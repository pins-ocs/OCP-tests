/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_Guess.cc                                   |
 |                                                                       |
 |  version: 1.0   date 3/6/2021                                         |
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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
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

  #define Xoptima__check__node__lt(A,B,MSG)   if ( (A) >= (B) ) { m_console->yellow(fmt::format("Failed check on cell={} segment={}: {}\n",ipos,i_segment,MSG),3); return false; }
  #define Xoptima__check__node__le(A,B,MSG)   if ( (A) >  (B) ) { m_console->yellow(fmt::format("Failed check on cell={} segment={}: {}\n",ipos,i_segment,MSG),3); return false; }
  #define Xoptima__check__cell__lt(A,B,MSG)   if ( (A) >= (B) ) { m_console->yellow(fmt::format("Failed check on node={} segment={}: {}\n",icell,i_segment,MSG),3); return false; }
  #define Xoptima__check__cell__le(A,B,MSG)   if ( (A) >  (B) ) { m_console->yellow(fmt::format("Failed check on node={} segment={}: {}\n",icell,i_segment,MSG),3); return false; }
  #define Xoptima__check__pars__lt(A,B,MSG)   if ( (A) >= (B) ) { m_console->yellow(fmt::format("Failed check on parameter: {}\n",MSG),3); return false; }
  #define Xoptima__check__pars__le(A,B,MSG)   if ( (A) >  (B) ) { m_console->yellow(fmt::format("Failed check on parameter: {}\n",MSG),3); return false; }
  #define Xoptima__check__params__lt(A,B,MSG) if ( (A) >= (B) ) { m_console->yellow(fmt::format("Failed check on model parameter: {}\n",MSG),3); return false; }
  #define Xoptima__check__params__le(A,B,MSG) if ( (A) >  (B) ) { m_console->yellow(fmt::format("Failed check on model parameter: {}\n",MSG),3); return false; }



  // node_check_strings
  #define Xoptima__message_node_check_0 "0 < 1+f(zeta)*cos(L(zeta))+g(zeta)*sin(L(zeta))"
  #define Xoptima__message_node_check_1 "0 < p(zeta)"


  // cell_check_strings
  #define Xoptima__message_cell_check_0 "0 < 1+f(zeta)*cos(L(zeta))+g(zeta)*sin(L(zeta))"



  bool
  gtocX_2burn::p_check( P_const_pointer_type P__ ) const {
    return true;
  }

  bool
  gtocX_2burn::xlambda_check_node(
    integer              ipos,
    NodeType2 const    & NODE__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t6   = sin(t2);
    Xoptima__check__node__lt(0, t3 * X__[iX_f] + t6 * X__[iX_g] + 1, Xoptima__message_node_check_0);
    Xoptima__check__node__lt(0, X__[iX_p], Xoptima__message_node_check_1);
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  gtocX_2burn::xlambda_check_cell(
    integer              icell,
    NodeType2 const    & NODE__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t6   = sin(t2);
    Xoptima__check__cell__lt(0, t3 * X__[iX_f] + t6 * X__[iX_g] + 1, Xoptima__message_cell_check_0);
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
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[6];
    real_type L__[6];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
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
    return xlambda_check_cell( icell, NODE__, P__ );
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
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    // no controls to check
    return ok;
  }

}

// EOF: gtocX_2burn_Methods_Guess.cc
