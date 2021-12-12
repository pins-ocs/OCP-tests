/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods_controls.cc                           |
 |                                                                       |
 |  version: 1.0   date 13/12/2021                                       |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  gtocX_2burn_pars::g_fun_eval(
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
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_muS];
    real_type t2   = sqrt(t1);
    real_type t4   = p_guess(0);
    real_type t5   = t4 * t4;
    real_type t6   = t2 * t5;
    real_type t7   = P__[iP_p];
    real_type t8   = sqrt(t7);
    real_type t9   = t8 * t7;
    real_type t11  = ModelPars[iM_w_guess] - 1;
    real_type t12  = t11 * t9;
    real_type t14  = ModelPars[iM_time_i];
    real_type t15  = ModelPars[iM_time_f] - t14;
    real_type t18  = QM__[0] * t15 + t14;
    real_type t19  = L_guess(t18, t14);
    real_type t20  = t19 * t19;
    real_type t23  = XM__[2];
    real_type t26  = t11 * t5;
    real_type t30  = XM__[0];
    real_type t31  = cos(t23);
    real_type t33  = XM__[1];
    real_type t34  = sin(t23);
    real_type t35  = t34 * t33;
    real_type t37  = ray_positive(t31 * t30 + t35 + 1);
    real_type t41  = f_guess(t18);
    real_type t42  = t41 * t41;
    real_type t50  = g_guess(t18);
    real_type t51  = t50 * t50;
    real_type t59  = t7 * t7;
    real_type t69  = ray(t7, t30, t33, t23);
    real_type t70  = acceleration_r(t69, t1);
    real_type t73  = P__[iP_h];
    real_type t74  = t73 * t73;
    real_type t75  = h_guess(0);
    real_type t78  = t23 * t23;
    real_type t79  = t30 * t30;
    real_type t80  = t33 * t33;
    real_type t81  = t75 * t75;
    real_type t82  = P__[iP_k];
    real_type t83  = t82 * t82;
    real_type t84  = k_guess(0);
    real_type t87  = t84 * t84;
    real_type t102 = t31 * t31;
    real_type t116 = t20 * t12 * t6 - 2 * t19 * t26 * t2 * t23 * t9 - t9 * t2 * t5 * t37 + t42 * t12 * t6 - 2 * t41 * t26 * t2 * t30 * t9 + t51 * t12 * t6 - 2 * t50 * t26 * t2 * t33 * t9 + t70 * (LM__[1] * t31 - LM__[0] * t34) * t15 * ModelPars[iM_w_nonlin] * t59 * t5 + t9 * t11 * (-2 * t75 * t73 - 2 * t84 * t82 + t74 + t78 + t79 + t80 + t81 + t83 + t87 + 1) * t6 - 2 * t8 * t59 * t11 * t4 * t2 + t8 * t59 * t7 * t11 * t2 - t1 * t5 * LM__[2] * t15 * (t102 * (t79 - t80) + t31 * (2 * t34 * t33 * t30 + 2 * t30) + t80 + 2 * t35 + 1);
    real_type result__ = -1.0 / t5 / t9 * t116 / t2;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  integer
  gtocX_2burn_pars::g_numEqns() const
  { return 0; }

  void
  gtocX_2burn_pars::g_eval(
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
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 0, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DgDxlxlp_numRows() const
  { return 0; }

  integer
  gtocX_2burn_pars::DgDxlxlp_numCols() const
  { return 15; }

  integer
  gtocX_2burn_pars::DgDxlxlp_nnz() const
  { return 0; }

  void
  gtocX_2burn_pars::DgDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DgDu_numRows() const
  { return 0; }

  integer
  gtocX_2burn_pars::DgDu_numCols() const
  { return 0; }

  integer
  gtocX_2burn_pars::DgDu_nnz() const
  { return 0; }

  void
  gtocX_2burn_pars::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DgDu_sparse(
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
  gtocX_2burn_pars::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    // no controls to compute
  }

  /*\
   |  ____        ____       _      _                           _       _   _
   | |  _ \ _   _|  _ \__  _| |_  _| |_ __     __ _ _ __   __ _| |_   _| |_(_) ___
   | | | | | | | | | | \ \/ / \ \/ / | '_ \   / _` | '_ \ / _` | | | | | __| |/ __|
   | | |_| | |_| | |_| |>  <| |>  <| | |_) | | (_| | | | | (_| | | |_| | |_| | (__
   | |____/ \__,_|____//_/\_\_/_/\_\_| .__/   \__,_|_| |_|\__,_|_|\__, |\__|_|\___|
   |                                 |_|                          |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       UM__,
    MatrixWrapper<real_type> & DuDxlxlp
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
  gtocX_2burn_pars::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_f];
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t5   = X__[iX_g];
    real_type t6   = sin(t2);
    real_type t8   = t3 * t1 + t6 * t5 + 1;
    real_type t9   = ray_positive(t8);
    real_type t13  = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t14  = P__[iP_p];
    real_type t15  = sqrt(t14);
    real_type t17  = ModelPars[iM_muS];
    real_type t18  = sqrt(t17);
    real_type t20  = 1.0 / t18 * t15 * t13;
    real_type t22  = ray(t14, t1, t5, t2);
    real_type t23  = acceleration_r(t22, t17);
    real_type t24  = t23 * ModelPars[iM_w_nonlin];
    real_type t28  = pow(-t6 * t24 * t20 + V__[0], 2);
    real_type t33  = pow(t3 * t24 * t20 + V__[1], 2);
    real_type t35  = t8 * t8;
    real_type t42  = pow(V__[2] - t18 / t15 / t14 * t35 * t13, 2);
    real_type result__ = t9 + t28 + t33 + t42;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::DmDu_numEqns() const
  { return 0; }

  void
  gtocX_2burn_pars::DmDu_eval(
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

  integer
  gtocX_2burn_pars::DmDuu_numRows() const
  { return 0; }

  integer
  gtocX_2burn_pars::DmDuu_numCols() const
  { return 0; }

  integer
  gtocX_2burn_pars::DmDuu_nnz() const
  { return 0; }

  void
  gtocX_2burn_pars::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: gtocX_2burn_pars_Methods_controls.cc
