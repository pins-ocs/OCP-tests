/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_Guess.cc                                   |
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


using namespace std;

namespace gtocX_2burnDefine {

  /*\
   |    ____
   |   / ___|_   _  ___  ___ ___
   |  | |  _| | | |/ _ \/ __/ __|
   |  | |_| | |_| |  __/\__ \__ \
   |   \____|\__,_|\___||___/___/
  \*/

  void
  gtocX_2burn::p_guess_eval( P_pointer_type P__ ) const {
  }

  void
  gtocX_2burn::xlambda_guess_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    P_const_pointer_type P__,
    X_pointer_type       X__,
    L_pointer_type       L__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = Q__[iQ_zeta];
    real_type t3   = ModelPars[iM_time_i];
    real_type t7   = t3 * (1 - t1) + ModelPars[iM_time_f] * t1;
    X__[ iX_p ] = p_guess(t7);
    X__[ iX_f ] = f_guess(t7);
    X__[ iX_g ] = g_guess(t7);
    X__[ iX_h ] = h_guess(t7);
    X__[ iX_k ] = k_guess(t7);
    X__[ iX_L ] = L_guess(t7, t3);

    if ( m_debug )
      Mechatronix::check( X__.pointer(), "xlambda_guess_eval (x part)", 6 );
    if ( m_debug )
      Mechatronix::check( L__.pointer(), "xlambda_guess_eval (lambda part)", 6 );
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
        "Failed check on cell={} segment={}: {}\nfail {} < {}\n",     \
        icell, i_segment, MSG, a, b                                   \
      ),3);                                                           \
      return false;                                                   \
    }                                                                 \
  }

  #define Xoptima__check__cell__le(A,B,MSG)                           \
  {                                                                   \
    real_type a = A, b = B;                                           \
    if ( a > b ) {                                                    \
      m_console->yellow(fmt::format(                                  \
        "Failed check on cell={} segment={}: {}\nfail {} <= {}\n",    \
        icell, i_segment, MSG, a, b                                   \
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
  #define Xoptima__message_node_check_0 "0 < p(zeta)"

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  gtocX_2burn::p_check( P_const_pointer_type P__ ) const {
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  gtocX_2burn::xlambda_check_node(
    integer              ipos,
    NodeType2 const    & NODE__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    Xoptima__check__node__lt(0, X__[iX_p], Xoptima__message_node_check_0);
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  gtocX_2burn::xlambda_check_cell(
    integer              icell,
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__
  ) const {
    return true;
  }

  /*\
   |   _   _        ____
   |  | | | |      / ___|_   _  ___  ___ ___
   |  | | | |_____| |  _| | | |/ _ \/ __/ __|
   |  | |_| |_____| |_| | |_| |  __/\__ \__ \
   |   \___/       \____|\__,_|\___||___/___/
  \*/

  integer
  gtocX_2burn::u_guess_numEqns() const
  { return 0; }

  void
  gtocX_2burn::u_guess_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    // no controls to initialize
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    // no controls to compute
  }

  /*\
   |   _   _        ____ _               _
   |  | | | |      / ___| |__   ___  ___| | __
   |  | | | |_____| |   | '_ \ / _ \/ __| |/ /
   |  | |_| |_____| |___| | | |  __/ (__|   <
   |   \___/       \____|_| |_|\___|\___|_|\_\
  \*/

  bool
  gtocX_2burn::u_check_if_admissible(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    bool ok = true;
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    // controls range check

    return ok;
  }

}

// EOF: gtocX_2burn_Methods_Guess.cc
