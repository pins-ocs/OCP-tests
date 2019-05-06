/*-----------------------------------------------------------------------*\
 |  file: farmer_problem_Methods.cc                                      |
 |                                                                       |
 |  version: 1.0   date 6/5/2019                                         |
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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  farmer_problem::DHxDx_numRows() const
  { return 5; }

  integer
  farmer_problem::DHxDx_numCols() const
  { return 5; }

  integer
  farmer_problem::DHxDx_nnz() const
  { return 16; }

  void
  farmer_problem::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 0   ; jIndex[ 3  ] = 4   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 0   ;
    iIndex[ 5  ] = 1   ; jIndex[ 5  ] = 1   ;
    iIndex[ 6  ] = 1   ; jIndex[ 6  ] = 2   ;
    iIndex[ 7  ] = 1   ; jIndex[ 7  ] = 4   ;
    iIndex[ 8  ] = 2   ; jIndex[ 8  ] = 0   ;
    iIndex[ 9  ] = 2   ; jIndex[ 9  ] = 1   ;
    iIndex[ 10 ] = 2   ; jIndex[ 10 ] = 2   ;
    iIndex[ 11 ] = 2   ; jIndex[ 11 ] = 4   ;
    iIndex[ 12 ] = 4   ; jIndex[ 12 ] = 0   ;
    iIndex[ 13 ] = 4   ; jIndex[ 13 ] = 1   ;
    iIndex[ 14 ] = 4   ; jIndex[ 14 ] = 2   ;
    iIndex[ 15 ] = 4   ; jIndex[ 15 ] = 4   ;
  }

  void
  farmer_problem::DHxDx_sparse(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    V_const_pointer_type V__,
    L_const_pointer_type L__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    real_type t1   = ModelPars[18];
    real_type t2   = ModelPars[10];
    real_type t3   = t2 * t2;
    result__[ 0   ] = 2 / t3 * t1 + 2 * t2 + 2 * ModelPars[14];
    real_type t8   = ModelPars[11];
    real_type t9   = 1.0 / t8;
    real_type t11  = 1.0 / t2;
    result__[ 1   ] = 2 * t11 * t9 * t1;
    real_type t13  = ModelPars[12];
    real_type t14  = 1.0 / t13;
    real_type t15  = t14 * t1;
    result__[ 2   ] = 2 * t11 * t15;
    real_type t17  = ModelPars[13];
    real_type t19  = 1.0 / t17 * t1;
    result__[ 3   ] = 2 * t11 * t19;
    result__[ 4   ] = result__[1];
    real_type t24  = ALIAS_LimitX2X4_DD(0.12e0 - X__[1] - X__[4]);
    real_type t25  = t8 * t8;
    result__[ 5   ] = t24 + 2 / t25 * t1 + 2 * t8 + 2 * ModelPars[15];
    result__[ 6   ] = 2 * t9 * t15;
    result__[ 7   ] = 2 * t9 * t19 + t24;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    real_type t35  = t13 * t13;
    result__[ 10  ] = 2 / t35 * t1 + 2 * t13 + 2 * ModelPars[16];
    result__[ 11  ] = 2 * t14 * t19;
    result__[ 12  ] = result__[3];
    result__[ 13  ] = result__[7];
    result__[ 14  ] = result__[11];
    real_type t41  = t17 * t17;
    result__[ 15  ] = t24 + 2 / t41 * t1 + 2 * t17 + 2 * ModelPars[17];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHxDx_sparse",16);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  farmer_problem::DHxDp_numRows() const
  { return 5; }

  integer
  farmer_problem::DHxDp_numCols() const
  { return 0; }

  integer
  farmer_problem::DHxDp_nnz() const
  { return 0; }

  void
  farmer_problem::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  farmer_problem::DHxDp_sparse(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    V_const_pointer_type V__,
    L_const_pointer_type L__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }
}

// EOF: farmer_problem_Methods.cc
