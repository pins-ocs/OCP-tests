/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Methods_Guess.cc                            |
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


#include "ICLOCS_StirredTank.hh"
#include "ICLOCS_StirredTank_Pars.hh"

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
#define ALIAS_x2bound_DD(__t1) x2bound.DD( __t1)
#define ALIAS_x2bound_D(__t1) x2bound.D( __t1)
#define ALIAS_x1bound_DD(__t1) x1bound.DD( __t1)
#define ALIAS_x1bound_D(__t1) x1bound.D( __t1)
#define ALIAS_tfbound_DD(__t1) tfbound.DD( __t1)
#define ALIAS_tfbound_D(__t1) tfbound.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace ICLOCS_StirredTankDefine {

  /*\
   |    ____
   |   / ___|_   _  ___  ___ ___
   |  | |  _| | | |/ _ \/ __/ __|
   |  | |_| | |_| |  __/\__ \__ \
   |   \____|\__,_|\___||___/___/
  \*/

  void
  ICLOCS_StirredTank::p_guess_eval( P_pointer_type P__ ) const {
    P__[ iP_T ] = ModelPars[iM_T_guess];
    if ( m_debug )
      Mechatronix::check( P__.pointer(), "p_guess_eval", 1 );
  }

  void
  ICLOCS_StirredTank::xlambda_guess_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    P_const_pointer_type P__,
    X_pointer_type       X__,
    L_pointer_type       L__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    X__[ iX_x1 ] = ModelPars[iM_x1_f];
    X__[ iX_x2 ] = ModelPars[iM_x2_f];

    if ( m_debug )
      Mechatronix::check( X__.pointer(), "xlambda_guess_eval (x part)", 2 );
    if ( m_debug )
      Mechatronix::check( L__.pointer(), "xlambda_guess_eval (lambda part)", 2 );
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
  #define Xoptima__message_node_check_0 "0 < x1(zeta)"
  #define Xoptima__message_node_check_2 "0 < x2(zeta)"
  #define Xoptima__message_node_check_1 "x1(zeta) < 1"
  #define Xoptima__message_node_check_3 "x2(zeta) < 1"


  // cell_check_strings
  #define Xoptima__message_cell_check_0 "0 < x1(zeta)"
  #define Xoptima__message_cell_check_2 "0 < x2(zeta)"
  #define Xoptima__message_cell_check_1 "x1(zeta) < 1"
  #define Xoptima__message_cell_check_3 "x2(zeta) < 1"


  // pars_check_strings
  #define Xoptima__message_pars_check_0 "10 < T"
  #define Xoptima__message_pars_check_1 "T < 200"


  bool
  ICLOCS_StirredTank::p_check( P_const_pointer_type P__ ) const {
    real_type t1   = P__[iP_T];
    Xoptima__check__pars__lt(10, t1, Xoptima__message_pars_check_0);
    Xoptima__check__pars__lt(t1, 200, Xoptima__message_pars_check_1);
    return true;
  }

  bool
  ICLOCS_StirredTank::xlambda_check_node(
    integer              ipos,
    NodeType2 const    & NODE__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[iX_x1];
    Xoptima__check__node__lt(0, t1, Xoptima__message_node_check_0);
    real_type t2   = X__[iX_x2];
    Xoptima__check__node__lt(0, t2, Xoptima__message_node_check_2);
    Xoptima__check__node__lt(t1, 1, Xoptima__message_node_check_1);
    Xoptima__check__node__lt(t2, 1, Xoptima__message_node_check_3);
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ICLOCS_StirredTank::xlambda_check_cell(
    integer              icell,
    NodeType2 const    & NODE__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[iX_x1];
    Xoptima__check__cell__lt(0, t1, Xoptima__message_cell_check_0);
    real_type t2   = X__[iX_x2];
    Xoptima__check__cell__lt(0, t2, Xoptima__message_cell_check_2);
    Xoptima__check__cell__lt(t1, 1, Xoptima__message_cell_check_1);
    Xoptima__check__cell__lt(t2, 1, Xoptima__message_cell_check_3);
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ICLOCS_StirredTank::xlambda_check_cell(
    integer              icell,
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[2];
    real_type L__[2];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
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
  ICLOCS_StirredTank::u_guess_numEqns() const
  { return 1; }

  void
  ICLOCS_StirredTank::u_guess_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
      MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    std::fill_n( UGUESS__.pointer(), 1, 0 );
    UGUESS__[ iU_u ] = ModelPars[iM_u_f];
    if ( m_debug )
      Mechatronix::check_in_segment( UGUESS__.pointer(), "u_guess_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[2];
    real_type L__[2];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q      = Q__;
    NODE__.x      = X__;
    NODE__.lambda = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
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
  ICLOCS_StirredTank::u_check_if_admissible(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    bool ok = true;
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    uControl.check_range(U__[iU_u], 0, 2);
    return ok;
  }

}

// EOF: ICLOCS_StirredTank_Methods_Guess.cc
