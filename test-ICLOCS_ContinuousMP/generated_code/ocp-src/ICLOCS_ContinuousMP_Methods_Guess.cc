/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_Guess.cc                           |
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


#include "ICLOCS_ContinuousMP.hh"
#include "ICLOCS_ContinuousMP_Pars.hh"

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
#define ALIAS_yy20Limitation_DD(__t1) yy20Limitation.DD( __t1)
#define ALIAS_yy20Limitation_D(__t1) yy20Limitation.D( __t1)
#define ALIAS_xx20Limitation_DD(__t1) xx20Limitation.DD( __t1)
#define ALIAS_xx20Limitation_D(__t1) xx20Limitation.D( __t1)
#define ALIAS_yy19Limitation_DD(__t1) yy19Limitation.DD( __t1)
#define ALIAS_yy19Limitation_D(__t1) yy19Limitation.D( __t1)
#define ALIAS_xx19Limitation_DD(__t1) xx19Limitation.DD( __t1)
#define ALIAS_xx19Limitation_D(__t1) xx19Limitation.D( __t1)
#define ALIAS_yy18Limitation_DD(__t1) yy18Limitation.DD( __t1)
#define ALIAS_yy18Limitation_D(__t1) yy18Limitation.D( __t1)
#define ALIAS_xx18Limitation_DD(__t1) xx18Limitation.DD( __t1)
#define ALIAS_xx18Limitation_D(__t1) xx18Limitation.D( __t1)
#define ALIAS_yy17Limitation_DD(__t1) yy17Limitation.DD( __t1)
#define ALIAS_yy17Limitation_D(__t1) yy17Limitation.D( __t1)
#define ALIAS_xx17Limitation_DD(__t1) xx17Limitation.DD( __t1)
#define ALIAS_xx17Limitation_D(__t1) xx17Limitation.D( __t1)
#define ALIAS_yy16Limitation_DD(__t1) yy16Limitation.DD( __t1)
#define ALIAS_yy16Limitation_D(__t1) yy16Limitation.D( __t1)
#define ALIAS_xx16Limitation_DD(__t1) xx16Limitation.DD( __t1)
#define ALIAS_xx16Limitation_D(__t1) xx16Limitation.D( __t1)
#define ALIAS_yy15Limitation_DD(__t1) yy15Limitation.DD( __t1)
#define ALIAS_yy15Limitation_D(__t1) yy15Limitation.D( __t1)
#define ALIAS_xx15Limitation_DD(__t1) xx15Limitation.DD( __t1)
#define ALIAS_xx15Limitation_D(__t1) xx15Limitation.D( __t1)
#define ALIAS_yy14Limitation_DD(__t1) yy14Limitation.DD( __t1)
#define ALIAS_yy14Limitation_D(__t1) yy14Limitation.D( __t1)
#define ALIAS_xx14Limitation_DD(__t1) xx14Limitation.DD( __t1)
#define ALIAS_xx14Limitation_D(__t1) xx14Limitation.D( __t1)
#define ALIAS_yy13Limitation_DD(__t1) yy13Limitation.DD( __t1)
#define ALIAS_yy13Limitation_D(__t1) yy13Limitation.D( __t1)
#define ALIAS_xx13Limitation_DD(__t1) xx13Limitation.DD( __t1)
#define ALIAS_xx13Limitation_D(__t1) xx13Limitation.D( __t1)
#define ALIAS_yy12Limitation_DD(__t1) yy12Limitation.DD( __t1)
#define ALIAS_yy12Limitation_D(__t1) yy12Limitation.D( __t1)
#define ALIAS_xx12Limitation_DD(__t1) xx12Limitation.DD( __t1)
#define ALIAS_xx12Limitation_D(__t1) xx12Limitation.D( __t1)
#define ALIAS_yy11Limitation_DD(__t1) yy11Limitation.DD( __t1)
#define ALIAS_yy11Limitation_D(__t1) yy11Limitation.D( __t1)
#define ALIAS_xx11Limitation_DD(__t1) xx11Limitation.DD( __t1)
#define ALIAS_xx11Limitation_D(__t1) xx11Limitation.D( __t1)
#define ALIAS_yy10Limitation_DD(__t1) yy10Limitation.DD( __t1)
#define ALIAS_yy10Limitation_D(__t1) yy10Limitation.D( __t1)
#define ALIAS_xx10Limitation_DD(__t1) xx10Limitation.DD( __t1)
#define ALIAS_xx10Limitation_D(__t1) xx10Limitation.D( __t1)
#define ALIAS_yy9Limitation_DD(__t1) yy9Limitation.DD( __t1)
#define ALIAS_yy9Limitation_D(__t1) yy9Limitation.D( __t1)
#define ALIAS_xx9Limitation_DD(__t1) xx9Limitation.DD( __t1)
#define ALIAS_xx9Limitation_D(__t1) xx9Limitation.D( __t1)
#define ALIAS_yy8Limitation_DD(__t1) yy8Limitation.DD( __t1)
#define ALIAS_yy8Limitation_D(__t1) yy8Limitation.D( __t1)
#define ALIAS_xx8Limitation_DD(__t1) xx8Limitation.DD( __t1)
#define ALIAS_xx8Limitation_D(__t1) xx8Limitation.D( __t1)
#define ALIAS_yy7Limitation_DD(__t1) yy7Limitation.DD( __t1)
#define ALIAS_yy7Limitation_D(__t1) yy7Limitation.D( __t1)
#define ALIAS_xx7Limitation_DD(__t1) xx7Limitation.DD( __t1)
#define ALIAS_xx7Limitation_D(__t1) xx7Limitation.D( __t1)
#define ALIAS_yy6Limitation_DD(__t1) yy6Limitation.DD( __t1)
#define ALIAS_yy6Limitation_D(__t1) yy6Limitation.D( __t1)
#define ALIAS_xx6Limitation_DD(__t1) xx6Limitation.DD( __t1)
#define ALIAS_xx6Limitation_D(__t1) xx6Limitation.D( __t1)
#define ALIAS_yy5Limitation_DD(__t1) yy5Limitation.DD( __t1)
#define ALIAS_yy5Limitation_D(__t1) yy5Limitation.D( __t1)
#define ALIAS_xx5Limitation_DD(__t1) xx5Limitation.DD( __t1)
#define ALIAS_xx5Limitation_D(__t1) xx5Limitation.D( __t1)
#define ALIAS_yy4Limitation_DD(__t1) yy4Limitation.DD( __t1)
#define ALIAS_yy4Limitation_D(__t1) yy4Limitation.D( __t1)
#define ALIAS_xx4Limitation_DD(__t1) xx4Limitation.DD( __t1)
#define ALIAS_xx4Limitation_D(__t1) xx4Limitation.D( __t1)
#define ALIAS_yy3Limitation_DD(__t1) yy3Limitation.DD( __t1)
#define ALIAS_yy3Limitation_D(__t1) yy3Limitation.D( __t1)
#define ALIAS_xx3Limitation_DD(__t1) xx3Limitation.DD( __t1)
#define ALIAS_xx3Limitation_D(__t1) xx3Limitation.D( __t1)
#define ALIAS_yy2Limitation_DD(__t1) yy2Limitation.DD( __t1)
#define ALIAS_yy2Limitation_D(__t1) yy2Limitation.D( __t1)
#define ALIAS_xx2Limitation_DD(__t1) xx2Limitation.DD( __t1)
#define ALIAS_xx2Limitation_D(__t1) xx2Limitation.D( __t1)
#define ALIAS_yy1Limitation_DD(__t1) yy1Limitation.DD( __t1)
#define ALIAS_yy1Limitation_D(__t1) yy1Limitation.D( __t1)
#define ALIAS_xx1Limitation_DD(__t1) xx1Limitation.DD( __t1)
#define ALIAS_xx1Limitation_D(__t1) xx1Limitation.D( __t1)
#define ALIAS_u20Limitation_DD(__t1) u20Limitation.DD( __t1)
#define ALIAS_u20Limitation_D(__t1) u20Limitation.D( __t1)
#define ALIAS_u19Limitation_DD(__t1) u19Limitation.DD( __t1)
#define ALIAS_u19Limitation_D(__t1) u19Limitation.D( __t1)
#define ALIAS_u18Limitation_DD(__t1) u18Limitation.DD( __t1)
#define ALIAS_u18Limitation_D(__t1) u18Limitation.D( __t1)
#define ALIAS_u17Limitation_DD(__t1) u17Limitation.DD( __t1)
#define ALIAS_u17Limitation_D(__t1) u17Limitation.D( __t1)
#define ALIAS_u16Limitation_DD(__t1) u16Limitation.DD( __t1)
#define ALIAS_u16Limitation_D(__t1) u16Limitation.D( __t1)
#define ALIAS_u15Limitation_DD(__t1) u15Limitation.DD( __t1)
#define ALIAS_u15Limitation_D(__t1) u15Limitation.D( __t1)
#define ALIAS_u14Limitation_DD(__t1) u14Limitation.DD( __t1)
#define ALIAS_u14Limitation_D(__t1) u14Limitation.D( __t1)
#define ALIAS_u13Limitation_DD(__t1) u13Limitation.DD( __t1)
#define ALIAS_u13Limitation_D(__t1) u13Limitation.D( __t1)
#define ALIAS_u12Limitation_DD(__t1) u12Limitation.DD( __t1)
#define ALIAS_u12Limitation_D(__t1) u12Limitation.D( __t1)
#define ALIAS_u11Limitation_DD(__t1) u11Limitation.DD( __t1)
#define ALIAS_u11Limitation_D(__t1) u11Limitation.D( __t1)
#define ALIAS_u10Limitation_DD(__t1) u10Limitation.DD( __t1)
#define ALIAS_u10Limitation_D(__t1) u10Limitation.D( __t1)
#define ALIAS_u9Limitation_DD(__t1) u9Limitation.DD( __t1)
#define ALIAS_u9Limitation_D(__t1) u9Limitation.D( __t1)
#define ALIAS_u8Limitation_DD(__t1) u8Limitation.DD( __t1)
#define ALIAS_u8Limitation_D(__t1) u8Limitation.D( __t1)
#define ALIAS_u7Limitation_DD(__t1) u7Limitation.DD( __t1)
#define ALIAS_u7Limitation_D(__t1) u7Limitation.D( __t1)
#define ALIAS_u6Limitation_DD(__t1) u6Limitation.DD( __t1)
#define ALIAS_u6Limitation_D(__t1) u6Limitation.D( __t1)
#define ALIAS_u5Limitation_DD(__t1) u5Limitation.DD( __t1)
#define ALIAS_u5Limitation_D(__t1) u5Limitation.D( __t1)
#define ALIAS_u4Limitation_DD(__t1) u4Limitation.DD( __t1)
#define ALIAS_u4Limitation_D(__t1) u4Limitation.D( __t1)
#define ALIAS_u3Limitation_DD(__t1) u3Limitation.DD( __t1)
#define ALIAS_u3Limitation_D(__t1) u3Limitation.D( __t1)
#define ALIAS_u2Limitation_DD(__t1) u2Limitation.DD( __t1)
#define ALIAS_u2Limitation_D(__t1) u2Limitation.D( __t1)
#define ALIAS_u1Limitation_DD(__t1) u1Limitation.DD( __t1)
#define ALIAS_u1Limitation_D(__t1) u1Limitation.D( __t1)


using namespace std;

namespace ICLOCS_ContinuousMPDefine {

  /*\
   |    ____
   |   / ___|_   _  ___  ___ ___
   |  | |  _| | | |/ _ \/ __/ __|
   |  | |_| | |_| |  __/\__ \__ \
   |   \____|\__,_|\___||___/___/
  \*/

  void
  ICLOCS_ContinuousMP::p_guess_eval( P_pointer_type P__ ) const {
    P__[ iP_u1  ] = 0;
    P__[ iP_u2  ] = 0;
    P__[ iP_u3  ] = 0;
    P__[ iP_u4  ] = 0;
    P__[ iP_u5  ] = 0;
    P__[ iP_u6  ] = 0;
    P__[ iP_u7  ] = 0;
    P__[ iP_u8  ] = 0;
    P__[ iP_u9  ] = 0;
    P__[ iP_u10 ] = 0;
    P__[ iP_u11 ] = 0;
    P__[ iP_u12 ] = 0;
    P__[ iP_u13 ] = 0;
    P__[ iP_u14 ] = 0;
    P__[ iP_u15 ] = 0;
    P__[ iP_u16 ] = 0;
    P__[ iP_u17 ] = 0;
    P__[ iP_u18 ] = 0;
    P__[ iP_u19 ] = 0;
    P__[ iP_u20 ] = 0;
    if ( m_debug )
      Mechatronix::check( P__.pointer(), "p_guess_eval", 20 );
  }

  void
  ICLOCS_ContinuousMP::xlambda_guess_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    P_const_pointer_type P__,
    X_pointer_type       X__,
    L_pointer_type       L__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    X__[ iX_x1   ] = 1;
    X__[ iX_x2   ] = 1;
    X__[ iX_x3   ] = 1;
    X__[ iX_x4   ] = 1;
    X__[ iX_x5   ] = 1;
    X__[ iX_x6   ] = 1;
    X__[ iX_x7   ] = 1;
    X__[ iX_x8   ] = 1;
    X__[ iX_x9   ] = 1;
    X__[ iX_x10  ] = 1;
    X__[ iX_x11  ] = 1;
    X__[ iX_x12  ] = 1;
    X__[ iX_x13  ] = 1;
    X__[ iX_x14  ] = 1;
    X__[ iX_x15  ] = 1;
    X__[ iX_x16  ] = 1;
    X__[ iX_x17  ] = 1;
    X__[ iX_x18  ] = 1;
    X__[ iX_x19  ] = 1;
    X__[ iX_x20  ] = 1;
    X__[ iX_y1   ] = 1;
    X__[ iX_y2   ] = 1;
    X__[ iX_y3   ] = 1;
    X__[ iX_y4   ] = 1;
    X__[ iX_y5   ] = 1;
    X__[ iX_y6   ] = 1;
    X__[ iX_y7   ] = 1;
    X__[ iX_y8   ] = 1;
    X__[ iX_y9   ] = 1;
    X__[ iX_y10  ] = 1;

    if ( m_debug )
      Mechatronix::check( X__.pointer(), "xlambda_guess_eval (x part)", 80 );
    if ( m_debug )
      Mechatronix::check( L__.pointer(), "xlambda_guess_eval (lambda part)", 80 );
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


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ICLOCS_ContinuousMP::p_check( P_const_pointer_type P__ ) const {
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ICLOCS_ContinuousMP::xlambda_check_node(
    integer              ipos,
    NodeType2 const    & NODE__,
    P_const_pointer_type P__
  ) const {
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ICLOCS_ContinuousMP::xlambda_check_cell(
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
  ICLOCS_ContinuousMP::u_guess_numEqns() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::u_guess_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    // no controls to initialize
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::u_guess_eval(
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
  ICLOCS_ContinuousMP::u_check_if_admissible(
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

// EOF: ICLOCS_ContinuousMP_Methods_Guess.cc
