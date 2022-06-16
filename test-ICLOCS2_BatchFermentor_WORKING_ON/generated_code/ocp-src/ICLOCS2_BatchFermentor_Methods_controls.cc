/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Methods_controls.cc                     |
 |                                                                       |
 |  version: 1.0   date 17/6/2022                                        |
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


#include "ICLOCS2_BatchFermentor.hh"
#include "ICLOCS2_BatchFermentor_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::PenaltyBarrier1DGreaterThan;
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
#define ALIAS_penalization_DD(__t1) Pen1D.evaluate_DD( __t1)
#define ALIAS_penalization_D(__t1) Pen1D.evaluate_D( __t1)
#define ALIAS_penalization(__t1) Pen1D.evaluate( __t1)


namespace ICLOCS2_BatchFermentorDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  ICLOCS2_BatchFermentor::g_fun_eval(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_WP];
    real_type t2   = XM__[0];
    real_type t3   = UM__[0];
    real_type t5   = pow(t2 - t3, 2);
    real_type t7   = XM__[1];
    real_type t8   = UM__[1];
    real_type t10  = pow(t7 - t8, 2);
    real_type t12  = XM__[2];
    real_type t13  = UM__[2];
    real_type t15  = pow(t12 - t13, 2);
    real_type t17  = XM__[3];
    real_type t18  = UM__[3];
    real_type t20  = pow(t17 - t18, 2);
    real_type t24  = 1.0 / ModelPars[iM_x_max] * t3;
    real_type t25  = ALIAS_penalization(t24);
    real_type t27  = ALIAS_penalization(1 - t24);
    real_type t30  = 1.0 / ModelPars[iM_p_max] * t8;
    real_type t31  = ALIAS_penalization(t30);
    real_type t33  = ALIAS_penalization(1 - t30);
    real_type t36  = 1.0 / ModelPars[iM_s_max] * t13;
    real_type t37  = ALIAS_penalization(t36);
    real_type t39  = ALIAS_penalization(1 - t36);
    real_type t41  = 1.0 / ModelPars[iM_v_max];
    real_type t42  = t41 * t18;
    real_type t43  = ALIAS_penalization(t42);
    real_type t45  = ALIAS_penalization(1 - t42);
    real_type t47  = ALIAS_penalization(t41 * t17);
    real_type t49  = UM__[4];
    real_type t50  = t49 * t49;
    real_type t52  = ModelPars[iM_epsilon];
    real_type t53  = t52 * t52;
    real_type t57  = log(1 + 1.0 / t53 * t50);
    real_type t61  = mu(t12, t2);
    real_type t62  = t2 * t61;
    real_type t63  = U(t49);
    real_type t65  = 1.0 / t17;
    real_type t70  = rho(t12);
    real_type t71  = t2 * t70;
    real_type result__ = t5 * t1 + t10 * t1 + t15 * t1 + t20 * t1 + t25 + t27 + t31 + t33 + t37 + t39 + t43 + t45 + t47 + t50 * ModelPars[iM_W] + t57 * t52 / 2 + (-t2 * t63 * t65 + t62) * LM__[0] + (-t63 * t65 * t7 - t7 * ModelPars[iM_K_degr] + t71) * LM__[1] + (-1.0 / ModelPars[iM_Yxs] * t62 - 1.0 / ModelPars[iM_Yes] * t71 - t2 / (ModelPars[iM_kappa_m] + t12) * t12 * ModelPars[iM_mu_s] + (ModelPars[iM_S_f] - t12) * t65 * t63) * LM__[2] + t63 * LM__[3];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS2_BatchFermentor::g_numEqns() const { return 5; }

  void
  ICLOCS2_BatchFermentor::g_eval(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_WP];
    real_type t2   = XM__[0];
    real_type t3   = UM__[0];
    real_type t8   = 1.0 / ModelPars[iM_x_max];
    real_type t9   = t8 * t3;
    real_type t10  = ALIAS_penalization_D(t9);
    real_type t13  = ALIAS_penalization_D(1 - t9);
    result__[ 0   ] = -2 * (t2 - t3) * t1 + t8 * t10 - t8 * t13;
    real_type t15  = XM__[1];
    real_type t16  = UM__[1];
    real_type t21  = 1.0 / ModelPars[iM_p_max];
    real_type t22  = t21 * t16;
    real_type t23  = ALIAS_penalization_D(t22);
    real_type t26  = ALIAS_penalization_D(1 - t22);
    result__[ 1   ] = -2 * (t15 - t16) * t1 + t21 * t23 - t21 * t26;
    real_type t28  = XM__[2];
    real_type t29  = UM__[2];
    real_type t34  = 1.0 / ModelPars[iM_s_max];
    real_type t35  = t34 * t29;
    real_type t36  = ALIAS_penalization_D(t35);
    real_type t39  = ALIAS_penalization_D(1 - t35);
    result__[ 2   ] = -2 * (t28 - t29) * t1 + t34 * t36 - t34 * t39;
    real_type t41  = XM__[3];
    real_type t42  = UM__[3];
    real_type t47  = 1.0 / ModelPars[iM_v_max];
    real_type t48  = t47 * t42;
    real_type t49  = ALIAS_penalization_D(t48);
    real_type t52  = ALIAS_penalization_D(1 - t48);
    result__[ 3   ] = -2 * (t41 - t42) * t1 + t47 * t49 - t47 * t52;
    real_type t55  = UM__[4];
    real_type t58  = ModelPars[iM_epsilon];
    real_type t60  = t55 * t55;
    real_type t61  = t58 * t58;
    real_type t67  = U_D(t55);
    real_type t68  = 1.0 / t41;
    real_type t69  = t68 * t67;
    result__[ 4   ] = 2 * t55 * ModelPars[iM_W] + 1.0 / (t60 + t61) * t55 * t58 - t69 * t2 * LM__[0] - t69 * t15 * LM__[1] + (ModelPars[iM_S_f] - t28) * t68 * t67 * LM__[2] + t67 * LM__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::DgDxlxlp_numRows() const { return 5; }
  integer ICLOCS2_BatchFermentor::DgDxlxlp_numCols() const { return 16; }
  integer ICLOCS2_BatchFermentor::DgDxlxlp_nnz()     const { return 24; }

  void
  ICLOCS2_BatchFermentor::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 8   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 10  ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 11  ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 1   ;
    iIndex[10] = 4   ; jIndex[10] = 2   ;
    iIndex[11] = 4   ; jIndex[11] = 3   ;
    iIndex[12] = 4   ; jIndex[12] = 4   ;
    iIndex[13] = 4   ; jIndex[13] = 5   ;
    iIndex[14] = 4   ; jIndex[14] = 6   ;
    iIndex[15] = 4   ; jIndex[15] = 7   ;
    iIndex[16] = 4   ; jIndex[16] = 8   ;
    iIndex[17] = 4   ; jIndex[17] = 9   ;
    iIndex[18] = 4   ; jIndex[18] = 10  ;
    iIndex[19] = 4   ; jIndex[19] = 11  ;
    iIndex[20] = 4   ; jIndex[20] = 12  ;
    iIndex[21] = 4   ; jIndex[21] = 13  ;
    iIndex[22] = 4   ; jIndex[22] = 14  ;
    iIndex[23] = 4   ; jIndex[23] = 15  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DgDxlxlp_sparse(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -0.10e1 * ModelPars[iM_WP];
    result__[ 1   ] = result__[0];
    result__[ 2   ] = result__[1];
    result__[ 3   ] = result__[2];
    result__[ 4   ] = result__[3];
    result__[ 5   ] = result__[4];
    result__[ 6   ] = result__[5];
    result__[ 7   ] = result__[6];
    real_type t3   = LM__[0];
    real_type t5   = U_D(UM__[4]);
    real_type t7   = XM__[3];
    real_type t8   = 1.0 / t7;
    result__[ 8   ] = -0.5e0 * t8 * t5 * t3;
    real_type t11  = LM__[1];
    result__[ 9   ] = -0.5e0 * t8 * t5 * t11;
    real_type t16  = t5 * LM__[2];
    result__[ 10  ] = -0.5e0 * t8 * t16;
    real_type t19  = XM__[0];
    real_type t21  = t7 * t7;
    real_type t22  = 1.0 / t21;
    real_type t23  = t22 * t5;
    real_type t26  = XM__[1];
    real_type t32  = ModelPars[iM_S_f] - XM__[2];
    result__[ 11  ] = 0.5e0 * t23 * t19 * t3 + 0.5e0 * t23 * t26 * t11 - 0.5e0 * t32 * t22 * t16;
    result__[ 12  ] = -0.5e0 * t8 * t5 * t19;
    result__[ 13  ] = -0.5e0 * t8 * t5 * t26;
    result__[ 14  ] = 0.5e0 * t32 * t8 * t5;
    result__[ 15  ] = 0.5e0 * t5;
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[9];
    result__[ 18  ] = result__[10];
    result__[ 19  ] = result__[11];
    result__[ 20  ] = result__[12];
    result__[ 21  ] = result__[13];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[15];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 24, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::DgDu_numRows() const { return 5; }
  integer ICLOCS2_BatchFermentor::DgDu_numCols() const { return 5; }
  integer ICLOCS2_BatchFermentor::DgDu_nnz()     const { return 5; }

  void
  ICLOCS2_BatchFermentor::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DgDu_sparse(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 2 * ModelPars[iM_WP];
    real_type t4   = ModelPars[iM_x_max];
    real_type t6   = 1.0 / t4 * UM__[0];
    real_type t7   = ALIAS_penalization_DD(t6);
    real_type t8   = t4 * t4;
    real_type t9   = 1.0 / t8;
    real_type t12  = ALIAS_penalization_DD(1 - t6);
    result__[ 0   ] = t9 * t12 + t9 * t7 + t2;
    real_type t15  = ModelPars[iM_p_max];
    real_type t17  = 1.0 / t15 * UM__[1];
    real_type t18  = ALIAS_penalization_DD(t17);
    real_type t19  = t15 * t15;
    real_type t20  = 1.0 / t19;
    real_type t23  = ALIAS_penalization_DD(1 - t17);
    result__[ 1   ] = t20 * t18 + t20 * t23 + t2;
    real_type t26  = ModelPars[iM_s_max];
    real_type t28  = 1.0 / t26 * UM__[2];
    real_type t29  = ALIAS_penalization_DD(t28);
    real_type t30  = t26 * t26;
    real_type t31  = 1.0 / t30;
    real_type t34  = ALIAS_penalization_DD(1 - t28);
    result__[ 2   ] = t31 * t29 + t31 * t34 + t2;
    real_type t37  = ModelPars[iM_v_max];
    real_type t39  = 1.0 / t37 * UM__[3];
    real_type t40  = ALIAS_penalization_DD(t39);
    real_type t41  = t37 * t37;
    real_type t42  = 1.0 / t41;
    real_type t45  = ALIAS_penalization_DD(1 - t39);
    result__[ 3   ] = t42 * t40 + t42 * t45 + t2;
    real_type t49  = ModelPars[iM_epsilon];
    real_type t50  = UM__[4];
    real_type t51  = t50 * t50;
    real_type t52  = t49 * t49;
    real_type t53  = t51 + t52;
    real_type t57  = t53 * t53;
    real_type t64  = U_DD(t50);
    real_type t66  = 1.0 / XM__[3];
    real_type t67  = t66 * t64;
    result__[ 4   ] = 2 * ModelPars[iM_W] + 1.0 / t53 * t49 - 2 / t57 * t51 * t49 - t67 * LM__[0] * XM__[0] - t67 * LM__[1] * XM__[1] + (ModelPars[iM_S_f] - XM__[2]) * t66 * t64 * LM__[2] + t64 * LM__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 5, i_segment );
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
  ICLOCS2_BatchFermentor::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    UTILS_ERROR(
      "ICLOCS2_BatchFermentor::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  ICLOCS2_BatchFermentor::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_s];
    real_type t3   = X__[iX_x];
    real_type t4   = mu(t2, t3);
    real_type t5   = t3 * t4;
    real_type t7   = U(U__[iU_w]);
    real_type t10  = 1.0 / X__[iX_v];
    real_type t13  = pow(t10 * t7 * t3 - t5 + V__[0], 2);
    real_type t15  = rho(t2);
    real_type t16  = t3 * t15;
    real_type t18  = X__[iX_p];
    real_type t23  = pow(t10 * t7 * t18 + t18 * ModelPars[iM_K_degr] - t16 + V__[1], 2);
    real_type t43  = pow(V__[2] + 1.0 / ModelPars[iM_Yxs] * t5 + 1.0 / ModelPars[iM_Yes] * t16 + t3 / (ModelPars[iM_kappa_m] + t2) * t2 * ModelPars[iM_mu_s] - (ModelPars[iM_S_f] - t2) * t10 * t7, 2);
    real_type t46  = pow(V__[3] - t7, 2);
    real_type result__ = t13 + t23 + t43 + t46;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS2_BatchFermentor::DmDu_numEqns() const { return 5; }

  void
  ICLOCS2_BatchFermentor::DmDu_eval(
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
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    real_type t2   = X__[iX_s];
    real_type t3   = X__[iX_x];
    real_type t4   = mu(t2, t3);
    real_type t5   = t3 * t4;
    real_type t6   = U__[iU_w];
    real_type t7   = U(t6);
    real_type t10  = 1.0 / X__[iX_v];
    real_type t14  = U_D(t6);
    real_type t15  = t10 * t14;
    real_type t18  = rho(t2);
    real_type t19  = t3 * t18;
    real_type t21  = X__[iX_p];
    real_type t44  = ModelPars[iM_S_f] - t2;
    result__[ 4   ] = 2 * t15 * t3 * (t10 * t7 * t3 - t5 + V__[0]) + 2 * t15 * t21 * (t10 * t7 * t21 + t21 * ModelPars[iM_K_degr] - t19 + V__[1]) - 2 * t44 * t10 * t14 * (V__[2] + 1.0 / ModelPars[iM_Yxs] * t5 + 1.0 / ModelPars[iM_Yes] * t19 + t3 / (ModelPars[iM_kappa_m] + t2) * t2 * ModelPars[iM_mu_s] - t44 * t10 * t7) - 2 * t14 * (V__[3] - t7);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::DmDuu_numRows() const { return 5; }
  integer ICLOCS2_BatchFermentor::DmDuu_numCols() const { return 5; }
  integer ICLOCS2_BatchFermentor::DmDuu_nnz()     const { return 1; }

  void
  ICLOCS2_BatchFermentor::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 4   ;
  }


  void
  ICLOCS2_BatchFermentor::DmDuu_sparse(
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
    real_type t1   = X__[iX_x];
    real_type t2   = t1 * t1;
    real_type t3   = U__[iU_w];
    real_type t4   = U_D(t3);
    real_type t5   = t4 * t4;
    real_type t7   = X__[iX_v];
    real_type t8   = t7 * t7;
    real_type t9   = 1.0 / t8;
    real_type t12  = X__[iX_s];
    real_type t13  = mu(t12, t1);
    real_type t14  = t1 * t13;
    real_type t15  = U(t3);
    real_type t17  = 1.0 / t7;
    real_type t21  = U_DD(t3);
    real_type t22  = t17 * t21;
    real_type t24  = X__[iX_p];
    real_type t25  = t24 * t24;
    real_type t29  = rho(t12);
    real_type t30  = t1 * t29;
    real_type t40  = ModelPars[iM_S_f] - t12;
    real_type t41  = t40 * t40;
    result__[ 0   ] = 2 * t9 * t5 * t2 + 2 * t22 * t1 * (t1 * t15 * t17 - t14 + V__[0]) + 2 * t9 * t5 * t25 + 2 * t22 * t24 * (t15 * t17 * t24 + t24 * ModelPars[iM_K_degr] - t30 + V__[1]) + 2 * t41 * t9 * t5 - 2 * t40 * t17 * t21 * (V__[2] + 1.0 / ModelPars[iM_Yxs] * t14 + 1.0 / ModelPars[iM_Yes] * t30 + t1 / (ModelPars[iM_kappa_m] + t12) * t12 * ModelPars[iM_mu_s] - t40 * t17 * t15) + 2 * t5 - 2 * t21 * (V__[3] - t15);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: ICLOCS2_BatchFermentor_Methods_controls.cc
