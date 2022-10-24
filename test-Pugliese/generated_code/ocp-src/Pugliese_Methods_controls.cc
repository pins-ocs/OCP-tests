/*-----------------------------------------------------------------------*\
 |  file: Pugliese_Methods_controls.cc                                   |
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


#include "Pugliese.hh"
#include "Pugliese_Pars.hh"

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


namespace PuglieseDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  Pugliese::g_fun_eval(
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
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XL__[iX_T];
    real_type t4   = ModelPars[iM_w2] * ModelPars[iM_a];
    real_type t5   = XL__[iX_I__p];
    real_type t6   = t5 * t5;
    real_type t7   = ModelPars[iM_b];
    real_type t12  = LM__[0];
    real_type t13  = ModelPars[iM_r];
    real_type t15  = 1.0 / ModelPars[iM_K];
    real_type t19  = XL__[iX_C];
    real_type t20  = T_lim(t1);
    real_type t22  = ModelPars[iM_kappa__AC];
    real_type t28  = LM__[1];
    real_type t29  = XL__[iX_DD];
    real_type t30  = D_lim(t29);
    real_type t31  = ModelPars[iM_mu__C];
    real_type t32  = IL(t1, t19);
    real_type t33  = IL_lim(t32);
    real_type t34  = ModelPars[iM_kappa__R];
    real_type t35  = XL__[iX_R];
    real_type t41  = LM__[2];
    real_type t42  = ModelPars[iM_a__R];
    real_type t44  = ModelPars[iM_mu__R];
    real_type t46  = ModelPars[iM_a__IL];
    real_type t50  = LM__[3];
    real_type t51  = ModelPars[iM_mu__D];
    real_type t53  = ModelPars[iM_rho__D];
    real_type t58  = ModelPars[iM_lambda] * LM__[4];
    real_type t60  = XR__[iX_T];
    real_type t61  = XR__[iX_I__p];
    real_type t62  = t61 * t61;
    real_type t70  = XR__[iX_C];
    real_type t71  = T_lim(t60);
    real_type t78  = XR__[iX_DD];
    real_type t79  = D_lim(t78);
    real_type t80  = IL(t60, t70);
    real_type t81  = IL_lim(t80);
    real_type t82  = XR__[iX_R];
    real_type result__ = t1 + 1.0 / (t6 + t7) * t6 * t4 + ((-t15 * t1 + 1) * t13 - t20 * t19 - t1 * t19 * t5 * t22) * t12 + (t30 - (t35 * t34 + t31 + t33) * t19) * t28 + (t29 * t42 + t32 * t46 - t35 * t44) * t41 + (-t51 * t29 + t53) * t50 - t5 * t58 + t60 + 1.0 / (t62 + t7) * t62 * t4 + ((-t15 * t60 + 1) * t13 - t71 * t70 - t60 * t70 * t61 * t22) * t12 + (t79 - (t82 * t34 + t31 + t81) * t70) * t28 + (t78 * t42 - t82 * t44 + t80 * t46) * t41 + (-t51 * t78 + t53) * t50 - t61 * t58;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Pugliese::g_numEqns() const { return 0; }

  void
  Pugliese::g_eval(
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
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 0, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Pugliese::DgDxlxlp_numRows() const { return 0; }
  integer Pugliese::DgDxlxlp_numCols() const { return 20; }
  integer Pugliese::DgDxlxlp_nnz()     const { return 0; }

  void
  Pugliese::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Pugliese::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Pugliese::DgDu_numRows() const { return 0; }
  integer Pugliese::DgDu_numCols() const { return 0; }
  integer Pugliese::DgDu_nnz()     const { return 0; }

  void
  Pugliese::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Pugliese::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
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
  Pugliese::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    // no controls to compute
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  Pugliese::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = X__[iX_T];
    real_type t9   = X__[iX_C];
    real_type t10  = T_lim(t3);
    real_type t13  = X__[iX_I__p];
    real_type t18  = pow(V__[0] - (1 - 1.0 / ModelPars[iM_K] * t3) * ModelPars[iM_r] + t10 * t9 + t3 * t9 * t13 * ModelPars[iM_kappa__AC], 2);
    real_type t20  = X__[iX_DD];
    real_type t21  = D_lim(t20);
    real_type t23  = IL(t3, t9);
    real_type t24  = IL_lim(t23);
    real_type t26  = X__[iX_R];
    real_type t31  = pow(V__[1] - t21 + (t26 * ModelPars[iM_kappa__R] + t24 + ModelPars[iM_mu__C]) * t9, 2);
    real_type t40  = pow(-t20 * ModelPars[iM_a__R] - t23 * ModelPars[iM_a__IL] + t26 * ModelPars[iM_mu__R] + V__[2], 2);
    real_type t46  = pow(t20 * ModelPars[iM_mu__D] + V__[3] - ModelPars[iM_rho__D], 2);
    real_type t51  = pow(t13 * ModelPars[iM_lambda] + V__[4], 2);
    real_type result__ = t18 + t31 + t40 + t46 + t51;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Pugliese::DmDu_numEqns() const { return 0; }

  void
  Pugliese::DmDu_eval(
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

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 0, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Pugliese::DmDuu_numRows() const { return 0; }
  integer Pugliese::DmDuu_numCols() const { return 0; }
  integer Pugliese::DmDuu_nnz()     const { return 0; }

  void
  Pugliese::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Pugliese::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: Pugliese_Methods_controls.cc
