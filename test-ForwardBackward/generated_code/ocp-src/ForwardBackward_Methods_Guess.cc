/*-----------------------------------------------------------------------*\
 |  file: ForwardBackward_Methods_Guess.cc                               |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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


#include "ForwardBackward.hh"
#include "ForwardBackward_Pars.hh"

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


using namespace std;

namespace ForwardBackwardDefine {

  /*\
   |    ____
   |   / ___|_   _  ___  ___ ___
   |  | |  _| | | |/ _ \/ __/ __|
   |  | |_| | |_| |  __/\__ \__ \
   |   \____|\__,_|\___||___/___/
  \*/

  void
  ForwardBackward::p_guess_eval( P_p_type P__ ) const {
  }

  void
  ForwardBackward::xlambda_guess_eval(
    integer        i_segment,
    Q_const_p_type Q__,
    P_const_p_type P__,
    X_p_type       X__,
    L_p_type       L__
  ) const {
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    { // open block to avoid temporary clash
      real_type t1   = ModelPars[iM_v0];
      X__[ iX_v ] = t1 + (ModelPars[iM_v1] - t1) * Q__[iQ_zeta];
    }
    { // open block to avoid temporary clash

    }
    if ( m_debug ) {
      Mechatronix::check( X__.pointer(), "xlambda_guess_eval (x part)", 1 );
      Mechatronix::check( L__.pointer(), "xlambda_guess_eval (lambda part)", 1 );
    }
  }

  /*\
   |    ____ _               _
   |   / ___| |__   ___  ___| | __
   |  | |   | '_ \ / _ \/ __| |/ /
   |  | |___| | | |  __/ (__|   <
   |   \____|_| |_|\___|\___|_|\_\
  \*/

  #define Xoptima__check__node__lt(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a >= b ) {                                                   \
      m_console->yellow(fmt::format(                                  \
        "Failed check on node={} segment={}: {}\nfail {} < {}\n",     \
        ipos, i_segment, MSG, a, b                                    \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__node__le(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a > b ) {                                                    \
      m_console->yellow(fmt::format(                                  \
        "Failed check on node={} segment={}: {}\nfail {} <= {}\n",    \
        ipos, i_segment, MSG, a, b                                    \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__cell__lt(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a >= b ) {                                                   \
      m_console->yellow(fmt::format(                                  \
        "Failed check on cell={}: {}\nfail {} < {}\n",                \
        icell, MSG, a, b                                              \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__cell__le(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a > b ) {                                                    \
      m_console->yellow(fmt::format(                                  \
        "Failed check on cell={}: {}\nfail {} <= {}\n",               \
        icell, MSG, a, b                                              \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__pars__lt(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a >= b ) {                                                   \
      m_console->yellow(fmt::format(                                  \
        "Failed check on parameter: {}\nfail {} < {}\n", MSG, a, b    \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__pars__le(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a > b ) {                                                    \
      m_console->yellow(fmt::format(                                  \
        "Failed check on parameter: {}\nfail {} <= {}\n", MSG, a, b   \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__params__lt(A,B,MSG)                         \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a >= b ) {                                                   \
      m_console->yellow(fmt::format(                                  \
        "Failed check on params: {}\nfail {} < {}\n", MSG, a, b       \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__params__le(A,B,MSG)                         \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a > b ) {                                                    \
      m_console->yellow(fmt::format(                                  \
        "Failed check on params: {}\nfail {} <= {}\n", MSG, a, b      \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__u__lt(A,B,MSG)                              \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a >= b ) {                                                   \
      m_U_console.yellow(fmt::format(                                 \
        "Failed check on control: {}\nfail {} < {}\n", MSG, a, b      \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__u__le(A,B,MSG)                              \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a > b ) {                                                    \
      m_U_console.yellow(fmt::format(                                 \
        "Failed check on control: {}\nfail {} <= {}\n", MSG, a, b     \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }


  // u_check_strings
  #define Xoptima__message_u_check_0 "WA*a(zeta)^2+kappa(zeta)^2*v(zeta)^4 < E_max^2"

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ForwardBackward::p_check( P_const_p_type P__ ) const {
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ForwardBackward::xlambda_check_node(
    integer         ipos,
    NodeQXL const & NODE__,
    P_const_p_type  P__
  ) const {
    return true;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
   |
  \*/

  bool
  ForwardBackward::penalties_check_node(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    bool ok = true;
    real_type t2   = X__[iX_v];
    ok = ok && LimitV_min.check_range(ModelPars[iM_v_min] - t2, m_max_penalty_value);
    ok = ok && LimitV_max.check_range(t2 - ModelPars[iM_v_max], m_max_penalty_value);
    real_type t7   = U__[iU_a];
    ok = ok && LimitA_min.check_range(ModelPars[iM_a_min] - t7, m_max_penalty_value);
    ok = ok && LimitA_max.check_range(t7 - ModelPars[iM_a_max], m_max_penalty_value);
    real_type t12  = t7 * t7;
    real_type t15  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t16  = t15 * t15;
    real_type t17  = t2 * t2;
    real_type t18  = t17 * t17;
    real_type t22  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    ok = ok && LimitE.check_range(1.0 / t22 * (t12 * ModelPars[iM_WA] + t18 * t16) - 1, m_max_penalty_value);
    return ok;
  }

  /*\
   |   _   _        ____
   |  | | | |      / ___|_   _  ___  ___ ___
   |  | | | |_____| |  _| | | |/ _ \/ __/ __|
   |  | |_| |_____| |_| | |_| |  __/\__ \__ \
   |   \___/       \____|\__,_|\___||___/___/
  \*/

  integer ForwardBackward::u_guess_numEqns() const { return 1; }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ForwardBackward::u_guess_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        UGUESS__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    std::fill_n( UGUESS__.pointer(), 1, 0 );
    UGUESS__[ iU_a ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( UGUESS__.pointer(), "u_guess_eval", 1, i_segment );
  }

  /*\
   |   _   _        ____ _               _
   |  | | | |      / ___| |__   ___  ___| | __
   |  | | | |_____| |   | '_ \ / _ \/ __| |/ /
   |  | |_| |_____| |___| | | |  __/ (__|   <
   |   \___/       \____|_| |_|\___|\___|_|\_\
  \*/

  bool
  ForwardBackward::u_check_if_admissible(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    bool ok = true;
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    // admissible region
    real_type t3   = U__[iU_a] * U__[iU_a];
    real_type t6   = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t7   = t6 * t6;
    real_type t9   = X__[iX_v] * X__[iX_v];
    real_type t10  = t9 * t9;
    real_type t14  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    /* REMOVED */ Xoptima__check__u__lt(t10 * t7 + t3 * ModelPars[iM_WA], t14, Xoptima__message_u_check_0);
    return ok;
  }

}

// EOF: ForwardBackward_Methods_Guess.cc
