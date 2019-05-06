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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  farmer_problem::g_numEqns() const
  { return 4; }

  void
  farmer_problem::g_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    L_const_pointer_type L__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    real_type t3   = U__[0];
    real_type t11  = ALIAS_x1__oControl_D_1(t3, -0.1e-2, 100);
    result__[ 0   ] = 2 * (-X__[0] + t3) * ModelPars[14] + L__[0] / ModelPars[5] + t11;
    real_type t14  = U__[1];
    real_type t22  = ALIAS_x2__oControl_D_1(t14, -0.1e-2, 100);
    result__[ 1   ] = 2 * (-X__[1] + t14) * ModelPars[15] + L__[1] / ModelPars[6] + t22;
    real_type t25  = U__[2];
    real_type t33  = ALIAS_x3__oControl_D_1(t25, -0.1e-2, 100);
    result__[ 2   ] = 2 * (-X__[2] + t25) * ModelPars[16] + L__[2] / ModelPars[7] + t33;
    real_type t36  = U__[3];
    real_type t44  = ALIAS_x4__oControl_D_1(t36, -0.1e-2, 100);
    result__[ 3   ] = 2 * (-X__[4] + t36) * ModelPars[17] + L__[4] / ModelPars[9] + t44;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"g_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  farmer_problem::DgDxlp_numRows() const
  { return 4; }

  integer
  farmer_problem::DgDxlp_numCols() const
  { return 10; }

  integer
  farmer_problem::DgDxlp_nnz() const
  { return 8; }

  void
  farmer_problem::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 5   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 1   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 6   ;
    iIndex[ 4  ] = 2   ; jIndex[ 4  ] = 2   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 7   ;
    iIndex[ 6  ] = 3   ; jIndex[ 6  ] = 4   ;
    iIndex[ 7  ] = 3   ; jIndex[ 7  ] = 9   ;
  }

  void
  farmer_problem::DgDxlp_sparse(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    L_const_pointer_type L__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    result__[ 0   ] = -2 * ModelPars[14];
    result__[ 1   ] = 1.0 / ModelPars[5];
    result__[ 2   ] = -2 * ModelPars[15];
    result__[ 3   ] = 1.0 / ModelPars[6];
    result__[ 4   ] = -2 * ModelPars[16];
    result__[ 5   ] = 1.0 / ModelPars[7];
    result__[ 6   ] = -2 * ModelPars[17];
    result__[ 7   ] = 1.0 / ModelPars[9];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDxlp_sparse",8);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  farmer_problem::DgDu_numRows() const
  { return 4; }

  integer
  farmer_problem::DgDu_numCols() const
  { return 4; }

  integer
  farmer_problem::DgDu_nnz() const
  { return 4; }

  void
  farmer_problem::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 3   ;
  }

  void
  farmer_problem::DgDu_sparse(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    L_const_pointer_type L__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    real_type t4   = ALIAS_x1__oControl_D_1_1(U__[0], -0.1e-2, 100);
    result__[ 0   ] = 2 * ModelPars[14] + t4;
    real_type t8   = ALIAS_x2__oControl_D_1_1(U__[1], -0.1e-2, 100);
    result__[ 1   ] = 2 * ModelPars[15] + t8;
    real_type t12  = ALIAS_x3__oControl_D_1_1(U__[2], -0.1e-2, 100);
    result__[ 2   ] = 2 * ModelPars[16] + t12;
    real_type t16  = ALIAS_x4__oControl_D_1_1(U__[3], -0.1e-2, 100);
    result__[ 3   ] = 2 * ModelPars[17] + t16;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDu_sparse",4);
    #endif
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  farmer_problem::A_numRows() const
  { return 5; }

  integer
  farmer_problem::A_numCols() const
  { return 5; }

  integer
  farmer_problem::A_nnz() const
  { return 5; }

  void
  farmer_problem::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 3   ;
    iIndex[ 4  ] = 4   ; jIndex[ 4  ] = 4   ;
  }

  void
  farmer_problem::A_sparse(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"A_sparse",5);
    #endif
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  integer
  farmer_problem::eta_numEqns() const
  { return 5; }

  void
  farmer_problem::eta_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    L_const_pointer_type L__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    result__[ 0   ] = L__[0];
    result__[ 1   ] = L__[1];
    result__[ 2   ] = L__[2];
    result__[ 3   ] = L__[3];
    result__[ 4   ] = L__[4];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"eta_eval",5);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  farmer_problem::DetaDx_numRows() const
  { return 5; }

  integer
  farmer_problem::DetaDx_numCols() const
  { return 5; }

  integer
  farmer_problem::DetaDx_nnz() const
  { return 0; }

  void
  farmer_problem::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  farmer_problem::DetaDx_sparse(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    L_const_pointer_type L__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  farmer_problem::DetaDp_numRows() const
  { return 5; }

  integer
  farmer_problem::DetaDp_numCols() const
  { return 0; }

  integer
  farmer_problem::DetaDp_nnz() const
  { return 0; }

  void
  farmer_problem::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  farmer_problem::DetaDp_sparse(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    L_const_pointer_type L__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  integer
  farmer_problem::nu_numEqns() const
  { return 5; }

  void
  farmer_problem::nu_eval(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"nu_eval",5);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  farmer_problem::DnuDx_numRows() const
  { return 5; }

  integer
  farmer_problem::DnuDx_numCols() const
  { return 5; }

  integer
  farmer_problem::DnuDx_nnz() const
  { return 0; }

  void
  farmer_problem::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  farmer_problem::DnuDx_sparse(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  farmer_problem::DnuDp_numRows() const
  { return 5; }

  integer
  farmer_problem::DnuDp_numCols() const
  { return 0; }

  integer
  farmer_problem::DnuDp_nnz() const
  { return 0; }

  void
  farmer_problem::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  farmer_problem::DnuDp_sparse(
    integer              i_segment,
    Q_const_pointer_type Q__,
    X_const_pointer_type X__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: farmer_problem_Methods.cc
