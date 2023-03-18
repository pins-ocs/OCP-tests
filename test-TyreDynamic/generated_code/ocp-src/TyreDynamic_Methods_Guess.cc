/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_Guess.cc                                   |
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


#include "TyreDynamic.hh"
#include "TyreDynamic_Pars.hh"

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
#define ALIAS_abs_reg_DD(__t1) abs_reg.DD( __t1)
#define ALIAS_abs_reg_D(__t1) abs_reg.D( __t1)
#define ALIAS_sign_reg_DD(__t1) sign_reg.DD( __t1)
#define ALIAS_sign_reg_D(__t1) sign_reg.D( __t1)
#define ALIAS_clipInt_D_3(__t1, __t2, __t3) clipInt.D_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2(__t1, __t2, __t3) clipInt.D_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1(__t1, __t2, __t3) clipInt.D_1( __t1, __t2, __t3)
#define ALIAS_clipInt_D_3_3(__t1, __t2, __t3) clipInt.D_3_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2_3(__t1, __t2, __t3) clipInt.D_2_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2_2(__t1, __t2, __t3) clipInt.D_2_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_3(__t1, __t2, __t3) clipInt.D_1_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_2(__t1, __t2, __t3) clipInt.D_1_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_1(__t1, __t2, __t3) clipInt.D_1_1( __t1, __t2, __t3)
#define ALIAS_clipSup_D_2(__t1, __t2) clipSup.D_2( __t1, __t2)
#define ALIAS_clipSup_D_1(__t1, __t2) clipSup.D_1( __t1, __t2)
#define ALIAS_clipSup_D_2_2(__t1, __t2) clipSup.D_2_2( __t1, __t2)
#define ALIAS_clipSup_D_1_2(__t1, __t2) clipSup.D_1_2( __t1, __t2)
#define ALIAS_clipSup_D_1_1(__t1, __t2) clipSup.D_1_1( __t1, __t2)
#define ALIAS_negPart_DD(__t1) negPart.DD( __t1)
#define ALIAS_negPart_D(__t1) negPart.D( __t1)
#define ALIAS_posPart_DD(__t1) posPart.DD( __t1)
#define ALIAS_posPart_D(__t1) posPart.D( __t1)
#define ALIAS_v_min_DD(__t1) v_min.DD( __t1)
#define ALIAS_v_min_D(__t1) v_min.D( __t1)
#define ALIAS_LongSlipRear_max_DD(__t1) LongSlipRear_max.DD( __t1)
#define ALIAS_LongSlipRear_max_D(__t1) LongSlipRear_max.D( __t1)
#define ALIAS_LongSlipRear_min_DD(__t1) LongSlipRear_min.DD( __t1)
#define ALIAS_LongSlipRear_min_D(__t1) LongSlipRear_min.D( __t1)
#define ALIAS_OnlyTractionRear_DD(__t1) OnlyTractionRear.DD( __t1)
#define ALIAS_OnlyTractionRear_D(__t1) OnlyTractionRear.D( __t1)
#define ALIAS_OnlyBrakingRear_DD(__t1) OnlyBrakingRear.DD( __t1)
#define ALIAS_OnlyBrakingRear_D(__t1) OnlyBrakingRear.D( __t1)
#define ALIAS_p__oControl_D_3(__t1, __t2, __t3) p__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2(__t1, __t2, __t3) p__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1(__t1, __t2, __t3) p__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_3_3(__t1, __t2, __t3) p__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2_3(__t1, __t2, __t3) p__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2_2(__t1, __t2, __t3) p__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_3(__t1, __t2, __t3) p__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_2(__t1, __t2, __t3) p__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_1(__t1, __t2, __t3) p__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_3(__t1, __t2, __t3) b__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2(__t1, __t2, __t3) b__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1(__t1, __t2, __t3) b__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_3_3(__t1, __t2, __t3) b__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2_3(__t1, __t2, __t3) b__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2_2(__t1, __t2, __t3) b__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_3(__t1, __t2, __t3) b__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_2(__t1, __t2, __t3) b__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_1(__t1, __t2, __t3) b__oControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace TyreDynamicDefine {

  /*\
   |    ____
   |   / ___|_   _  ___  ___ ___
   |  | |  _| | | |/ _ \/ __/ __|
   |  | |_| | |_| |  __/\__ \__ \
   |   \____|\__,_|\___||___/___/
  \*/

  void
  TyreDynamic::p_guess_eval( P_p_type P__ ) const {
  }

  void
  TyreDynamic::xlambda_guess_eval(
    integer        i_segment,
    Q_const_p_type Q__,
    P_const_p_type P__,
    X_p_type       X__,
    L_p_type       L__
  ) const {
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    { // open block to avoid temporary clash
      X__[ iX_v      ] = ModelPars[iM_v__ss];
      X__[ iX_omega  ] = ModelPars[iM_omega__ss];
      X__[ iX_lambda ] = ModelPars[iM_lambda__ss];
      X__[ iX_p      ] = ModelPars[iM_p__ss];
      X__[ iX_b      ] = ModelPars[iM_b__ss];
    }
    { // open block to avoid temporary clash

    }
    if ( m_debug ) {
      Mechatronix::check( X__.pointer(), "xlambda_guess_eval (x part)", 5 );
      Mechatronix::check( L__.pointer(), "xlambda_guess_eval (lambda part)", 5 );
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


  // node_check_strings
  #define Xoptima__message_node_check_0 "v__adm < v(zeta)"

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  TyreDynamic::p_check( P_const_p_type P__ ) const {
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  TyreDynamic::xlambda_check_node(
    integer         ipos,
    NodeQXL const & NODE__,
    P_const_p_type  P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    /* REMOVED */ Xoptima__check__node__lt(ModelPars[iM_v__adm], X__[iX_v], Xoptima__message_node_check_0);
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
  TyreDynamic::penalties_check(
    NodeQX const & NODE__,
    P_const_p_type P__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    bool ok = true;
    real_type t2   = ModelPars[iM_h__b];
    ok = ok && OnlyBrakingRear.check_range(X__[iX_b] - t2);
    ok = ok && OnlyTractionRear.check_range(-t2 - X__[iX_p]);
    real_type t9   = 1.0 / ModelPars[iM_lambda__max] * X__[iX_lambda];
    ok = ok && LongSlipRear_min.check_range(-1 - t9);
    ok = ok && LongSlipRear_max.check_range(t9 - 1);
    ok = ok && v_min.check_range(1 - X__[iX_v]);
    return ok;
  }

  /*\
   |   _   _        ____
   |  | | | |      / ___|_   _  ___  ___ ___
   |  | | | |_____| |  _| | | |/ _ \/ __/ __|
   |  | |_| |_____| |_| | |_| |  __/\__ \__ \
   |   \___/       \____|\__,_|\___||___/___/
  \*/

  integer TyreDynamic::u_guess_numEqns() const { return 2; }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TyreDynamic::u_guess_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        UGUESS__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    std::fill_n( UGUESS__.pointer(), 2, 0 );
    UGUESS__[ iU_p__o ] = 0;
    UGUESS__[ iU_b__o ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( UGUESS__.pointer(), "u_guess_eval", 2, i_segment );
  }

  /*\
   |   _   _        ____ _               _
   |  | | | |      / ___| |__   ___  ___| | __
   |  | | | |_____| |   | '_ \ / _ \/ __| |/ /
   |  | |_| |_____| |___| | | |  __/ (__|   <
   |   \___/       \____|_| |_|\___|\___|_|\_\
  \*/

  bool
  TyreDynamic::u_check_if_admissible(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    bool ok = true;
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    // controls range check
    ok = ok && b__oControl.check_range(U__[iU_b__o], -1, 1);
    ok = ok && p__oControl.check_range(U__[iU_p__o], -1, 1);
    return ok;
  }

}

// EOF: TyreDynamic_Methods_Guess.cc
