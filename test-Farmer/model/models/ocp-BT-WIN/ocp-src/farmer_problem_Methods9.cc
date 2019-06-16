/*-----------------------------------------------------------------------*\
 |  file: farmer_problem_Methods.cc                                      |
 |                                                                       |
 |  version: 1.0   date 16/6/2019                                        |
 |                                                                       |
 |  Copyright (C) 2019                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "farmer_problem.hh"
#include "farmer_problem_Pars.hh"

using namespace std;
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

// user class in namespaces
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
#define ALIAS_LimitX2X4_DD(__t1) LimitX2X4.DD( __t1)
#define ALIAS_LimitX2X4_D(__t1) LimitX2X4.D( __t1)
#define ALIAS_x4__oControl_D_3(__t1, __t2, __t3) x4__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_2(__t1, __t2, __t3) x4__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1(__t1, __t2, __t3) x4__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_3_3(__t1, __t2, __t3) x4__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_2_3(__t1, __t2, __t3) x4__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_2_2(__t1, __t2, __t3) x4__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1_3(__t1, __t2, __t3) x4__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1_2(__t1, __t2, __t3) x4__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1_1(__t1, __t2, __t3) x4__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_3(__t1, __t2, __t3) x3__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_2(__t1, __t2, __t3) x3__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1(__t1, __t2, __t3) x3__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_3_3(__t1, __t2, __t3) x3__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_2_3(__t1, __t2, __t3) x3__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_2_2(__t1, __t2, __t3) x3__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1_3(__t1, __t2, __t3) x3__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1_2(__t1, __t2, __t3) x3__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1_1(__t1, __t2, __t3) x3__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_3(__t1, __t2, __t3) x2__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_2(__t1, __t2, __t3) x2__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1(__t1, __t2, __t3) x2__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_3_3(__t1, __t2, __t3) x2__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_2_3(__t1, __t2, __t3) x2__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_2_2(__t1, __t2, __t3) x2__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1_3(__t1, __t2, __t3) x2__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1_2(__t1, __t2, __t3) x2__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1_1(__t1, __t2, __t3) x2__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_3(__t1, __t2, __t3) x1__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_2(__t1, __t2, __t3) x1__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1(__t1, __t2, __t3) x1__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_3_3(__t1, __t2, __t3) x1__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_2_3(__t1, __t2, __t3) x1__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_2_2(__t1, __t2, __t3) x1__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1_3(__t1, __t2, __t3) x1__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1_2(__t1, __t2, __t3) x1__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1_1(__t1, __t2, __t3) x1__oControl.D_1_1( __t1, __t2, __t3)


namespace farmer_problemDefine {

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  integer
  farmer_problem::u_numEqns() const
  { return 4; }

  void
  farmer_problem::u_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    L_const_pointer_type L__,
    U_const_pointer_type U_guess__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    if ( u_solve_iterative ) {
      u_standard_eval( i_segment, Q__, X__, L__, U_guess__, P__, U__ );
    } else {
      MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

       U__[ iU_x1__o ] = 0;
       U__[ iU_x2__o ] = 0;
       U__[ iU_x3__o ] = 0;
       U__[ iU_x4__o ] = 0;
    }
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(U__.pointer(),"u_eval",4);
    #endif
  }

  void
  farmer_problem::DuDxlp_full(
    integer                    i_segment,
    Q_const_pointer_type       Q__,
    X_const_pointer_type       X__,
    L_const_pointer_type       L__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    if ( u_solve_iterative ) {
      DuDxlp_standard_full( i_segment, Q__, X__, L__, P__, U__, DuDxlp );
    } else {
      
    DuDxlp(0, 0) = 0;
    DuDxlp(1, 0) = 0;
    DuDxlp(2, 0) = 0;
    DuDxlp(3, 0) = 0;
    DuDxlp(0, 1) = 0;
    DuDxlp(1, 1) = 0;
    DuDxlp(2, 1) = 0;
    DuDxlp(3, 1) = 0;
    DuDxlp(0, 2) = 0;
    DuDxlp(1, 2) = 0;
    DuDxlp(2, 2) = 0;
    DuDxlp(3, 2) = 0;
    DuDxlp(0, 3) = 0;
    DuDxlp(1, 3) = 0;
    DuDxlp(2, 3) = 0;
    DuDxlp(3, 3) = 0;
    DuDxlp(0, 4) = 0;
    DuDxlp(1, 4) = 0;
    DuDxlp(2, 4) = 0;
    DuDxlp(3, 4) = 0;
    DuDxlp(0, 5) = 0;
    DuDxlp(1, 5) = 0;
    DuDxlp(2, 5) = 0;
    DuDxlp(3, 5) = 0;
    DuDxlp(0, 6) = 0;
    DuDxlp(1, 6) = 0;
    DuDxlp(2, 6) = 0;
    DuDxlp(3, 6) = 0;
    DuDxlp(0, 7) = 0;
    DuDxlp(1, 7) = 0;
    DuDxlp(2, 7) = 0;
    DuDxlp(3, 7) = 0;
    DuDxlp(0, 8) = 0;
    DuDxlp(1, 8) = 0;
    DuDxlp(2, 8) = 0;
    DuDxlp(3, 8) = 0;
    DuDxlp(0, 9) = 0;
    DuDxlp(1, 9) = 0;
    DuDxlp(2, 9) = 0;
    DuDxlp(3, 9) = 0;
    }
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer
  farmer_problem::segmentLink_numEqns() const
  { return 0; }

  void
  farmer_problem::segmentLink_eval(
    integer              i_segment_left,
    Q_const_pointer_type qL,
    X_const_pointer_type xL,

    integer              i_segment_right,
    Q_const_pointer_type qR,
    X_const_pointer_type xR,

    P_const_pointer_type p,

    real_type            segmentLink[]
  ) const {
    ASSERT(false,"NON IMPLEMENTATA");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  farmer_problem::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  farmer_problem::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  farmer_problem::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  farmer_problem::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    ASSERT(false,"NON IMPLEMENTATA");
  }

  void
  farmer_problem::DsegmentLinkDxp_sparse(
    integer              i_segment_left,
    Q_const_pointer_type qL,
    X_const_pointer_type xL,

    integer              i_segment_right,
    Q_const_pointer_type qR,
    X_const_pointer_type xR,

    P_const_pointer_type p,

    real_type            DsegmentLinkDxp[]
  ) const {
    ASSERT(false,"NON IMPLEMENTATA");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer
  farmer_problem::jump_numEqns() const
  { return 10; }

  void
  farmer_problem::jump_eval(
    integer              i_segment_left,
    Q_const_pointer_type QL__,
    X_const_pointer_type XL__,
    L_const_pointer_type LL__,
    integer              i_segment_right,
    Q_const_pointer_type QR__,
    X_const_pointer_type XR__,
    L_const_pointer_type LR__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);

    result__[ 0   ] = XR__[0] - XL__[0];
    result__[ 1   ] = XR__[1] - XL__[1];
    result__[ 2   ] = XR__[2] - XL__[2];
    result__[ 3   ] = XR__[3] - XL__[3];
    result__[ 4   ] = XR__[4] - XL__[4];
    result__[ 5   ] = LR__[0] - LL__[0];
    result__[ 6   ] = LR__[1] - LL__[1];
    result__[ 7   ] = LR__[2] - LL__[2];
    result__[ 8   ] = LR__[3] - LL__[3];
    result__[ 9   ] = LR__[4] - LL__[4];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"jump_eval",10);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  farmer_problem::DjumpDxlp_numRows() const
  { return 10; }

  integer
  farmer_problem::DjumpDxlp_numCols() const
  { return 20; }

  integer
  farmer_problem::DjumpDxlp_nnz() const
  { return 20; }

  void
  farmer_problem::DjumpDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 10  ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 1   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 11  ;
    iIndex[ 4  ] = 2   ; jIndex[ 4  ] = 2   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 12  ;
    iIndex[ 6  ] = 3   ; jIndex[ 6  ] = 3   ;
    iIndex[ 7  ] = 3   ; jIndex[ 7  ] = 13  ;
    iIndex[ 8  ] = 4   ; jIndex[ 8  ] = 4   ;
    iIndex[ 9  ] = 4   ; jIndex[ 9  ] = 14  ;
    iIndex[ 10 ] = 5   ; jIndex[ 10 ] = 5   ;
    iIndex[ 11 ] = 5   ; jIndex[ 11 ] = 15  ;
    iIndex[ 12 ] = 6   ; jIndex[ 12 ] = 6   ;
    iIndex[ 13 ] = 6   ; jIndex[ 13 ] = 16  ;
    iIndex[ 14 ] = 7   ; jIndex[ 14 ] = 7   ;
    iIndex[ 15 ] = 7   ; jIndex[ 15 ] = 17  ;
    iIndex[ 16 ] = 8   ; jIndex[ 16 ] = 8   ;
    iIndex[ 17 ] = 8   ; jIndex[ 17 ] = 18  ;
    iIndex[ 18 ] = 9   ; jIndex[ 18 ] = 9   ;
    iIndex[ 19 ] = 9   ; jIndex[ 19 ] = 19  ;
  }

  void
  farmer_problem::DjumpDxlp_sparse(
    integer              i_segment_left,
    Q_const_pointer_type QL__,
    X_const_pointer_type XL__,
    L_const_pointer_type LL__,
    integer              i_segment_right,
    Q_const_pointer_type QR__,
    X_const_pointer_type XR__,
    L_const_pointer_type LR__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);

    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    result__[ 7   ] = 1;
    result__[ 8   ] = -1;
    result__[ 9   ] = 1;
    result__[ 10  ] = -1;
    result__[ 11  ] = 1;
    result__[ 12  ] = -1;
    result__[ 13  ] = 1;
    result__[ 14  ] = -1;
    result__[ 15  ] = 1;
    result__[ 16  ] = -1;
    result__[ 17  ] = 1;
    result__[ 18  ] = -1;
    result__[ 19  ] = 1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DjumpDxlp_sparse",20);
    #endif
  }

}

// EOF: farmer_problem_Methods.cc
