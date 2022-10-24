/*-----------------------------------------------------------------------*\
 |  file: ForwardBackward_Methods_controls.cc                            |
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


#include "ForwardBackward.hh"
#include "ForwardBackward_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::Path2D;


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
#define ALIAS_theta_DD(__t1) pTrajectory -> heading_DD( __t1)
#define ALIAS_theta_D(__t1) pTrajectory -> heading_D( __t1)
#define ALIAS_theta(__t1) pTrajectory -> heading( __t1)
#define ALIAS_yLane_DD(__t1) pTrajectory -> y_trajectory_DD( __t1)
#define ALIAS_yLane_D(__t1) pTrajectory -> y_trajectory_D( __t1)
#define ALIAS_yLane(__t1) pTrajectory -> y_trajectory( __t1)
#define ALIAS_xLane_DD(__t1) pTrajectory -> x_trajectory_DD( __t1)
#define ALIAS_xLane_D(__t1) pTrajectory -> x_trajectory_D( __t1)
#define ALIAS_xLane(__t1) pTrajectory -> x_trajectory( __t1)
#define ALIAS_kappa_DD(__t1) pTrajectory -> curvature_DD( __t1)
#define ALIAS_kappa_D(__t1) pTrajectory -> curvature_D( __t1)
#define ALIAS_kappa(__t1) pTrajectory -> curvature( __t1)
#define ALIAS_LimitE_DD(__t1) LimitE.DD( __t1)
#define ALIAS_LimitE_D(__t1) LimitE.D( __t1)
#define ALIAS_LimitA_max_DD(__t1) LimitA_max.DD( __t1)
#define ALIAS_LimitA_max_D(__t1) LimitA_max.D( __t1)
#define ALIAS_LimitA_min_DD(__t1) LimitA_min.DD( __t1)
#define ALIAS_LimitA_min_D(__t1) LimitA_min.D( __t1)
#define ALIAS_LimitV_max_DD(__t1) LimitV_max.DD( __t1)
#define ALIAS_LimitV_max_D(__t1) LimitV_max.D( __t1)
#define ALIAS_LimitV_min_DD(__t1) LimitV_min.DD( __t1)
#define ALIAS_LimitV_min_D(__t1) LimitV_min.D( __t1)


namespace ForwardBackwardDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  ForwardBackward::g_fun_eval(
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
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_wT];
    real_type t2   = XL__[iX_v];
    real_type t3   = 1.0 / t2;
    real_type t6   = UM__[0];
    real_type t7   = t6 * t6;
    real_type t10  = LM__[0];
    real_type t12  = ModelPars[iM_c0];
    real_type t13  = ModelPars[iM_c1];
    real_type t17  = ModelPars[iM_v_min];
    real_type t19  = LimitV_min(t17 - t2);
    real_type t20  = ModelPars[iM_v_max];
    real_type t22  = LimitV_max(t2 - t20);
    real_type t25  = LimitA_min(ModelPars[iM_a_min] - t6);
    real_type t29  = LimitA_max(t6 - ModelPars[iM_a_max]);
    real_type t32  = t7 * ModelPars[iM_WA];
    real_type t34  = ALIAS_kappa(QL__[iQ_zeta]);
    real_type t35  = t34 * t34;
    real_type t36  = t2 * t2;
    real_type t37  = t36 * t36;
    real_type t41  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t42  = 1.0 / t41;
    real_type t45  = LimitE(t42 * (t37 * t35 + t32) - 1);
    real_type t46  = XR__[iX_v];
    real_type t47  = 1.0 / t46;
    real_type t54  = LimitV_min(t17 - t46);
    real_type t56  = LimitV_max(t46 - t20);
    real_type t58  = ALIAS_kappa(QR__[iQ_zeta]);
    real_type t59  = t58 * t58;
    real_type t60  = t46 * t46;
    real_type t61  = t60 * t60;
    real_type t66  = LimitE(t42 * (t61 * t59 + t32) - 1);
    real_type result__ = t3 * t1 + 2 * t7 * ModelPars[iM_epsilon] + (-t2 * t13 + t3 * t6 - t12) * t10 + t19 + t22 + 2 * t25 + 2 * t29 + t45 + t47 * t1 + (-t46 * t13 + t47 * t6 - t12) * t10 + t54 + t56 + t66;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::g_numEqns() const { return 1; }

  void
  ForwardBackward::g_eval(
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
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = UM__[0];
    real_type t5   = LM__[0];
    real_type t6   = XL__[iX_v];
    real_type t11  = ALIAS_LimitA_min_D(ModelPars[iM_a_min] - t2);
    real_type t15  = ALIAS_LimitA_max_D(t2 - ModelPars[iM_a_max]);
    real_type t17  = ModelPars[iM_WA];
    real_type t18  = t2 * t2;
    real_type t19  = t18 * t17;
    real_type t21  = ALIAS_kappa(QL__[iQ_zeta]);
    real_type t22  = t21 * t21;
    real_type t23  = t6 * t6;
    real_type t24  = t23 * t23;
    real_type t28  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t29  = 1.0 / t28;
    real_type t32  = ALIAS_LimitE_D(t29 * (t22 * t24 + t19) - 1);
    real_type t34  = t29 * t2;
    real_type t37  = XR__[iX_v];
    real_type t41  = ALIAS_kappa(QR__[iQ_zeta]);
    real_type t42  = t41 * t41;
    real_type t43  = t37 * t37;
    real_type t44  = t43 * t43;
    real_type t49  = ALIAS_LimitE_D(t29 * (t42 * t44 + t19) - 1);
    result__[ 0   ] = 4 * t2 * ModelPars[iM_epsilon] + 1.0 / t6 * t5 - 2 * t11 + 2 * t15 + 2 * t34 * t17 * t32 + 1.0 / t37 * t5 + 2 * t34 * t17 * t49;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DgDxlxlp_numRows() const { return 1; }
  integer ForwardBackward::DgDxlxlp_numCols() const { return 4; }
  integer ForwardBackward::DgDxlxlp_nnz()     const { return 4; }

  void
  ForwardBackward::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ForwardBackward::DgDxlxlp_sparse(
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
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t2   = XL__[iX_v];
    real_type t3   = t2 * t2;
    real_type t6   = ModelPars[iM_WA];
    real_type t7   = UM__[0];
    real_type t8   = t7 * t7;
    real_type t9   = t8 * t6;
    real_type t11  = ALIAS_kappa(QL__[iQ_zeta]);
    real_type t12  = t11 * t11;
    real_type t13  = t3 * t3;
    real_type t17  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t18  = 1.0 / t17;
    real_type t21  = ALIAS_LimitE_DD(t18 * (t13 * t12 + t9) - 1);
    real_type t25  = t17 * t17;
    real_type t28  = t7 * t6 / t25;
    result__[ 0   ] = -1.0 / t3 * t1 + 8 * t28 * t3 * t2 * t12 * t21;
    real_type t33  = XR__[iX_v];
    result__[ 1   ] = 0.5e0 / t2 + 0.5e0 / t33;
    real_type t36  = t33 * t33;
    real_type t40  = ALIAS_kappa(QR__[iQ_zeta]);
    real_type t41  = t40 * t40;
    real_type t42  = t36 * t36;
    real_type t47  = ALIAS_LimitE_DD(t18 * (t42 * t41 + t9) - 1);
    result__[ 2   ] = -1.0 / t36 * t1 + 8 * t28 * t36 * t33 * t41 * t47;
    result__[ 3   ] = result__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DgDu_numRows() const { return 1; }
  integer ForwardBackward::DgDu_numCols() const { return 1; }
  integer ForwardBackward::DgDu_nnz()     const { return 1; }

  void
  ForwardBackward::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ForwardBackward::DgDu_sparse(
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
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t4   = UM__[0];
    real_type t6   = ALIAS_LimitA_min_DD(ModelPars[iM_a_min] - t4);
    real_type t10  = ALIAS_LimitA_max_DD(t4 - ModelPars[iM_a_max]);
    real_type t12  = ModelPars[iM_WA];
    real_type t13  = t4 * t4;
    real_type t14  = t13 * t12;
    real_type t16  = ALIAS_kappa(QL__[iQ_zeta]);
    real_type t17  = t16 * t16;
    real_type t19  = XL__[iX_v] * XL__[iX_v];
    real_type t20  = t19 * t19;
    real_type t24  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t25  = 1.0 / t24;
    real_type t27  = t25 * (t20 * t17 + t14) - 1;
    real_type t28  = ALIAS_LimitE_DD(t27);
    real_type t29  = t12 * t12;
    real_type t31  = t24 * t24;
    real_type t33  = 1.0 / t31 * t13;
    real_type t36  = ALIAS_LimitE_D(t27);
    real_type t41  = ALIAS_kappa(QR__[iQ_zeta]);
    real_type t42  = t41 * t41;
    real_type t44  = XR__[iX_v] * XR__[iX_v];
    real_type t45  = t44 * t44;
    real_type t49  = t25 * (t45 * t42 + t14) - 1;
    real_type t50  = ALIAS_LimitE_DD(t49);
    real_type t54  = ALIAS_LimitE_D(t49);
    result__[ 0   ] = 2 * t25 * t12 * t36 + 2 * t25 * t12 * t54 + 4 * t33 * t29 * t28 + 4 * t33 * t29 * t50 + 2 * t10 + 2 * t6 + 4 * ModelPars[iM_epsilon];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 1, i_segment );
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
  ForwardBackward::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    UTILS_ERROR(
      "ForwardBackward::u_eval_analytic\n"
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
  ForwardBackward::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t4   = LimitV_min(ModelPars[iM_v_min] - t2);
    real_type t7   = LimitV_max(t2 - ModelPars[iM_v_max]);
    real_type t9   = U__[iU_a];
    real_type t11  = LimitA_min(ModelPars[iM_a_min] - t9);
    real_type t14  = LimitA_max(t9 - ModelPars[iM_a_max]);
    real_type t16  = t9 * t9;
    real_type t19  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t20  = t19 * t19;
    real_type t21  = t2 * t2;
    real_type t22  = t21 * t21;
    real_type t26  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t30  = LimitE(1.0 / t26 * (t16 * ModelPars[iM_WA] + t22 * t20) - 1);
    real_type t38  = pow(V__[0] - 1.0 / t2 * t9 + ModelPars[iM_c0] + t2 * ModelPars[iM_c1], 2);
    real_type result__ = t4 + t7 + t11 + t14 + t30 + t38;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::DmDu_numEqns() const { return 1; }

  void
  ForwardBackward::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_a];
    real_type t4   = ALIAS_LimitA_min_D(ModelPars[iM_a_min] - t2);
    real_type t7   = ALIAS_LimitA_max_D(t2 - ModelPars[iM_a_max]);
    real_type t8   = ModelPars[iM_WA];
    real_type t9   = t2 * t2;
    real_type t12  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t13  = t12 * t12;
    real_type t14  = X__[iX_v];
    real_type t15  = t14 * t14;
    real_type t16  = t15 * t15;
    real_type t20  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t21  = 1.0 / t20;
    real_type t24  = ALIAS_LimitE_D(t21 * (t16 * t13 + t9 * t8) - 1);
    real_type t30  = 1.0 / t14;
    result__[ 0   ] = -t4 + t7 + 2 * t21 * t2 * t8 * t24 - 2 * t30 * (t14 * ModelPars[iM_c1] - t30 * t2 + V__[0] + ModelPars[iM_c0]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DmDuu_numRows() const { return 1; }
  integer ForwardBackward::DmDuu_numCols() const { return 1; }
  integer ForwardBackward::DmDuu_nnz()     const { return 1; }

  void
  ForwardBackward::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  ForwardBackward::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_a];
    real_type t4   = ALIAS_LimitA_min_DD(ModelPars[iM_a_min] - t2);
    real_type t7   = ALIAS_LimitA_max_DD(t2 - ModelPars[iM_a_max]);
    real_type t8   = ModelPars[iM_WA];
    real_type t9   = t2 * t2;
    real_type t12  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t13  = t12 * t12;
    real_type t15  = X__[iX_v] * X__[iX_v];
    real_type t16  = t15 * t15;
    real_type t20  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t21  = 1.0 / t20;
    real_type t23  = t21 * (t16 * t13 + t9 * t8) - 1;
    real_type t24  = ALIAS_LimitE_DD(t23);
    real_type t25  = t8 * t8;
    real_type t27  = t20 * t20;
    real_type t32  = ALIAS_LimitE_D(t23);
    result__[ 0   ] = t4 + t7 + 4 / t27 * t9 * t25 * t24 + 2 * t21 * t8 * t32 + 2 / t15;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: ForwardBackward_Methods_controls.cc
