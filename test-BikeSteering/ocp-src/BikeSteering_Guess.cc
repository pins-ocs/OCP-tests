/*-----------------------------------------------------------------------*\
 |  file: BikeSteering_Guess.cc                                          |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "BikeSteering.hh"
#include "BikeSteering_Pars.hh"

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
#define ALIAS_minimumTimeSize_DD(__t1) minimumTimeSize.DD( __t1)
#define ALIAS_minimumTimeSize_D(__t1) minimumTimeSize.D( __t1)
#define ALIAS_FyControl_D_3(__t1, __t2, __t3) FyControl.D_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2(__t1, __t2, __t3) FyControl.D_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1(__t1, __t2, __t3) FyControl.D_1( __t1, __t2, __t3)
#define ALIAS_FyControl_D_3_3(__t1, __t2, __t3) FyControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2_3(__t1, __t2, __t3) FyControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2_2(__t1, __t2, __t3) FyControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_3(__t1, __t2, __t3) FyControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_2(__t1, __t2, __t3) FyControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_1(__t1, __t2, __t3) FyControl.D_1_1( __t1, __t2, __t3)


namespace BikeSteeringDefine {

  using namespace std;

  /*\
   |    ____
   |   / ___|_   _  ___  ___ ___
   |  | |  _| | | |/ _ \/ __/ __|
   |  | |_| | |_| |  __/\__ \__ \
   |   \____|\__,_|\___||___/___/
  \*/

  void
  BikeSteering::p_guess_eval( P_pointer_type P__ ) const {
  }

  void
  BikeSteering::xlambda_guess_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    P_const_pointer_type P__,
    X_pointer_type       X__,
    L_pointer_type       L__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    X__[ iX_TimeSize ] = 1;

  }

  /*\
   |    ____ _               _
   |   / ___| |__   ___  ___| | __
   |  | |   | '_ \ / _ \/ __| |/ /
   |  | |___| | | |  __/ (__|   <
   |   \____|_| |_|\___|\___|_|\_\
  \*/

  #define Xoptima__check__lt(A,B) ( (A) <  (B) )
  #define Xoptima__check__le(A,B) ( (A) <= (B) )

  bool
  BikeSteering::p_check( P_const_pointer_type P__ ) const {
    bool ok = true;

    return ok;
  }

  bool
  BikeSteering::xlambda_check_node(
    integer              ipos,
    NodeType2 const    & NODE__,
    P_const_pointer_type P__
  ) const {
    bool ok = true;
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    return ok;
  }

  bool
  BikeSteering::xlambda_check_cell(
    integer              icell,
    NodeType2 const    & NODE__,
    P_const_pointer_type P__
  ) const {
    return true;
  }

  bool
  BikeSteering::xlambda_check_cell(
    integer              icell,
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__
  ) const {
    return true;
  }
}

// EOF: BikeSteering_Guess.cc
