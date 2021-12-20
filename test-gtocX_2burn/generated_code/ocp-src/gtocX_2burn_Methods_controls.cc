/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_controls.cc                                |
 |                                                                       |
 |  version: 1.0   date 20/12/2021                                       |
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
    real_type t1   = ModelPars[iM_muS];
    real_type t2   = sqrt(t1);
    real_type t4   = XM__[0];
    real_type t5   = sqrt(t4);
    real_type t6   = t5 * t4;
    real_type t10  = ModelPars[iM_time_i];
    real_type t11  = ModelPars[iM_time_f] - t10;
    real_type t14  = QM__[0] * t11 + t10;
    real_type t15  = p_guess(t14);
    real_type t16  = t15 * t15;
    real_type t19  = -1 + ModelPars[iM_w_guess];
    real_type t20  = t19 * t6;
    real_type t21  = L_guess(t14, t10);
    real_type t22  = t21 * t21;
    real_type t25  = t6 * t2;
    real_type t27  = XM__[5];
    real_type t32  = XM__[1];
    real_type t33  = cos(t27);
    real_type t35  = XM__[2];
    real_type t36  = sin(t27);
    real_type t37  = t36 * t35;
    real_type t39  = ray_positive(t33 * t32 + t37 + 1);
    real_type t42  = f_guess(t14);
    real_type t43  = t42 * t42;
    real_type t50  = g_guess(t14);
    real_type t51  = t50 * t50;
    real_type t58  = h_guess(t14);
    real_type t59  = t58 * t58;
    real_type t62  = XM__[3];
    real_type t67  = k_guess(t14);
    real_type t68  = t67 * t67;
    real_type t71  = XM__[4];
    real_type t76  = t4 * t4;
    real_type t85  = ray(t4, t32, t35, t27);
    real_type t86  = acceleration_r(t85, t1);
    real_type t89  = t32 * t32;
    real_type t90  = t35 * t35;
    real_type t91  = t62 * t62;
    real_type t92  = t71 * t71;
    real_type t93  = t27 * t27;
    real_type t100 = t33 * t33;
    real_type t111 = -t43 * t19 * t25 + 2 * t42 * t19 * t32 * t25 - t51 * t19 * t25 + 2 * t50 * t19 * t35 * t25 - t59 * t19 * t25 + 2 * t58 * t20 * t2 * t62 - t68 * t19 * t25 + 2 * t67 * t20 * t2 * t71 - t86 * (LM__[2] * t33 - LM__[1] * t36) * t11 * ModelPars[iM_w_nonlin] * t76 - t20 * (t89 + t90 + t91 + t92 + t93 + 1) * t2 + (t100 * (t89 - t90) + t33 * (2 * t35 * t32 * t36 + 2 * t32) + 2 * t37 + t90 + 1) * t11 * LM__[5] * t1;
    real_type result__ = 1.0 / t16 * (2 * t15 * t19 * t5 * t76 * t2 + 2 * t21 * t19 * t27 * t16 * t25 - t19 * t2 * t5 * t76 * t4 - t22 * t20 * t2 * t16 + t25 * t16 * t39 + t16 * t111) / t6 / t2;
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
