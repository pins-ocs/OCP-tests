/*-----------------------------------------------------------------------*\
 |  file: BangBangFredundant_Methods_Guess.cc                            |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
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


#include "BangBangFredundant.hh"
#include "BangBangFredundant_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_Flim_max_DD(__t1) Flim_max.DD( __t1)
#define ALIAS_Flim_max_D(__t1) Flim_max.D( __t1)
#define ALIAS_Flim_min_DD(__t1) Flim_min.DD( __t1)
#define ALIAS_Flim_min_D(__t1) Flim_min.D( __t1)
#define ALIAS_aF2Control_D_3(__t1, __t2, __t3) aF2Control.D_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2(__t1, __t2, __t3) aF2Control.D_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1(__t1, __t2, __t3) aF2Control.D_1( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_3_3(__t1, __t2, __t3) aF2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2_3(__t1, __t2, __t3) aF2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2_2(__t1, __t2, __t3) aF2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_3(__t1, __t2, __t3) aF2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_2(__t1, __t2, __t3) aF2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_1(__t1, __t2, __t3) aF2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_3(__t1, __t2, __t3) aF1Control.D_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2(__t1, __t2, __t3) aF1Control.D_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1(__t1, __t2, __t3) aF1Control.D_1( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_3_3(__t1, __t2, __t3) aF1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2_3(__t1, __t2, __t3) aF1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2_2(__t1, __t2, __t3) aF1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_3(__t1, __t2, __t3) aF1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_2(__t1, __t2, __t3) aF1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_1(__t1, __t2, __t3) aF1Control.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace BangBangFredundantDefine {

  /*\
   |    ____
   |   / ___|_   _  ___  ___ ___
   |  | |  _| | | |/ _ \/ __/ __|
   |  | |_| | |_| |  __/\__ \__ \
   |   \____|\__,_|\___||___/___/
  \*/

  void
  BangBangFredundant::p_guess_eval( P_pointer_type P__ ) const {
  }

  void
  BangBangFredundant::xlambda_guess_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    P_const_pointer_type P__,
    X_pointer_type       X__,
    L_pointer_type       L__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = Q__[iQ_zeta];
    X__[ iX_v   ] = (1 - t1) * t1;

    if ( m_debug ) {
      Mechatronix::check( X__.pointer(), "xlambda_guess_eval (x part)", 6 );
      Mechatronix::check( L__.pointer(), "xlambda_guess_eval (lambda part)", 6 );
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


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  BangBangFredundant::p_check( P_const_pointer_type P__ ) const {
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  BangBangFredundant::xlambda_check_node(
    integer              ipos,
    NodeType2 const    & NODE__,
    P_const_pointer_type P__
  ) const {
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  BangBangFredundant::xlambda_check_cell(
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

  integer BangBangFredundant::u_guess_numEqns() const { return 2; }

  void
  BangBangFredundant::u_guess_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    std::fill_n( UGUESS__.pointer(), 2, 0 );
    UGUESS__[ iU_aF1 ] = 0;
    UGUESS__[ iU_aF2 ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( UGUESS__.pointer(), "u_guess_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFredundant::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[6];
    real_type L__[6];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q      = Q__;
    NODE__.x      = X__;
    NODE__.lambda = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    X__[4] = (LEFT__.x[4]+RIGHT__.x[4])/2;
    X__[5] = (LEFT__.x[5]+RIGHT__.x[5])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    L__[5] = (LEFT__.lambda[5]+RIGHT__.lambda[5])/2;
    this->u_guess_eval( NODE__, P__, UGUESS__ );
  }

  /*\
   |   _   _        ____ _               _
   |  | | | |      / ___| |__   ___  ___| | __
   |  | | | |_____| |   | '_ \ / _ \/ __| |/ /
   |  | |_| |_____| |___| | | |  __/ (__|   <
   |   \___/       \____|_| |_|\___|\___|_|\_\
  \*/

  bool
  BangBangFredundant::u_check_if_admissible(
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
    real_type t2   = ModelPars[iM_maxAF];
    aF1Control.check_range(U__[iU_aF1], -t2, t2);
    aF2Control.check_range(U__[iU_aF2], -t2, t2);
    return ok;
  }

}

// EOF: BangBangFredundant_Methods_Guess.cc
