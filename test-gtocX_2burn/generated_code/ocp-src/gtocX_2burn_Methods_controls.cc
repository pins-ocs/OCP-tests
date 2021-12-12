/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_controls.cc                                |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  gtocX_2burn::g_fun_eval(
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
    real_type QM__[1], XM__[6], LM__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XM__[0];
    real_type t2   = sqrt(t1);
    real_type t3   = t2 * t1;
    real_type t6   = ModelPars[iM_time_i];
    real_type t7   = ModelPars[iM_time_f] - t6;
    real_type t10  = QM__[0] * t7 + t6;
    real_type t11  = p_guess(t10);
    real_type t12  = t11 * t11;
    real_type t13  = ModelPars[iM_muS];
    real_type t14  = sqrt(t13);
    real_type t17  = ModelPars[iM_w_guess] - 1;
    real_type t18  = t17 * t3;
    real_type t19  = L_guess(t10, t6);
    real_type t20  = t19 * t19;
    real_type t23  = t3 * t14;
    real_type t25  = XM__[5];
    real_type t30  = XM__[1];
    real_type t31  = cos(t25);
    real_type t33  = XM__[2];
    real_type t34  = sin(t25);
    real_type t35  = t34 * t33;
    real_type t37  = ray_positive(t31 * t30 + t35 + 1);
    real_type t40  = f_guess(t10);
    real_type t41  = t40 * t40;
    real_type t48  = g_guess(t10);
    real_type t49  = t48 * t48;
    real_type t56  = h_guess(t10);
    real_type t57  = t56 * t56;
    real_type t60  = XM__[3];
    real_type t65  = k_guess(t10);
    real_type t66  = t65 * t65;
    real_type t69  = XM__[4];
    real_type t74  = t1 * t1;
    real_type t83  = ray(t1, t30, t33, t25);
    real_type t84  = acceleration_r(t83, t13);
    real_type t87  = t30 * t30;
    real_type t88  = t33 * t33;
    real_type t89  = t60 * t60;
    real_type t90  = t69 * t69;
    real_type t91  = t25 * t25;
    real_type t97  = t31 * t31;
    real_type t109 = -t41 * t17 * t23 + 2 * t40 * t17 * t30 * t23 - t49 * t17 * t23 + 2 * t48 * t17 * t33 * t23 - t57 * t17 * t23 + 2 * t56 * t18 * t14 * t60 - t66 * t17 * t23 + 2 * t65 * t18 * t14 * t69 - t84 * (LM__[2] * t31 - LM__[1] * t34) * t7 * ModelPars[iM_w_nonlin] * t74 - t18 * (t87 + t88 + t89 + t90 + t91 + 1) * t14 + t13 * t7 * (t97 * (t87 - t88) + t31 * (2 * t33 * t30 * t34 + 2 * t30) + 2 * t35 + t88 + 1) * LM__[5];
    real_type result__ = 1.0 / t12 / t14 * (-t17 * t14 * t2 * t74 * t1 + 2 * t11 * t17 * t2 * t74 * t14 + 2 * t19 * t17 * t25 * t12 * t23 - t20 * t18 * t14 * t12 + t23 * t12 * t37 + t12 * t109) / t3;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  integer
  gtocX_2burn::g_numEqns() const
  { return 0; }

  void
  gtocX_2burn::g_eval(
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
    real_type QM__[1], XM__[6], LM__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 0, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn::DgDxlxlp_numRows() const
  { return 0; }

  integer
  gtocX_2burn::DgDxlxlp_numCols() const
  { return 24; }

  integer
  gtocX_2burn::DgDxlxlp_nnz() const
  { return 0; }

  void
  gtocX_2burn::DgDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::DgDxlxlp_sparse(
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
  gtocX_2burn::DgDu_numRows() const
  { return 0; }

  integer
  gtocX_2burn::DgDu_numCols() const
  { return 0; }

  integer
  gtocX_2burn::DgDu_nnz() const
  { return 0; }

  void
  gtocX_2burn::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::DgDu_sparse(
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
  gtocX_2burn::u_eval_analytic(
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
  gtocX_2burn::DuDxlxlp_full_analytic(
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
  gtocX_2burn::m_eval(
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
    real_type t11  = V__[0] * V__[0];
    real_type t15  = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t16  = X__[iX_p];
    real_type t17  = sqrt(t16);
    real_type t19  = ModelPars[iM_muS];
    real_type t20  = sqrt(t19);
    real_type t22  = 1.0 / t20 * t17 * t15;
    real_type t24  = ray(t16, t1, t5, t2);
    real_type t25  = acceleration_r(t24, t19);
    real_type t26  = t25 * ModelPars[iM_w_nonlin];
    real_type t30  = pow(-t6 * t26 * t22 + V__[1], 2);
    real_type t35  = pow(t3 * t26 * t22 + V__[2], 2);
    real_type t37  = V__[3] * V__[3];
    real_type t39  = V__[4] * V__[4];
    real_type t41  = t8 * t8;
    real_type t48  = pow(V__[5] - t20 / t17 / t16 * t41 * t15, 2);
    real_type result__ = t9 + t11 + t30 + t35 + t37 + t39 + t48;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn::DmDu_numEqns() const
  { return 0; }

  void
  gtocX_2burn::DmDu_eval(
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
  gtocX_2burn::DmDuu_numRows() const
  { return 0; }

  integer
  gtocX_2burn::DmDuu_numCols() const
  { return 0; }

  integer
  gtocX_2burn::DmDuu_nnz() const
  { return 0; }

  void
  gtocX_2burn::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: gtocX_2burn_Methods_controls.cc
