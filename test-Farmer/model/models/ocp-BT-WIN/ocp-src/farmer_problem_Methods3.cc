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
   |   ___                   _
   |  | _ ) ___ _  _ _ _  __| |__ _ _ _ _  _
   |  | _ \/ _ \ || | ' \/ _` / _` | '_| || |
   |  |___/\___/\_,_|_||_\__,_\__,_|_|  \_, |
   |    ___             _ _ _   _       |__/
   |   / __|___ _ _  __| (_) |_(_)___ _ _  ___
   |  | (__/ _ \ ' \/ _` | |  _| / _ \ ' \(_-<
   |   \___\___/_||_\__,_|_|\__|_\___/_||_/__/
  \*/

  integer
  farmer_problem::boundaryConditions_numEqns() const
  { return 5; }

  void
  farmer_problem::boundaryConditions_eval(
    integer              i_segment_left,
    Q_const_pointer_type QL__,
    X_const_pointer_type XL__,
    integer              i_segment_right,
    Q_const_pointer_type QR__,
    X_const_pointer_type XR__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);

    result__[ 0   ] = XL__[0] - ModelPars[19];
    result__[ 1   ] = XL__[1] - ModelPars[20];
    result__[ 2   ] = XL__[2] - ModelPars[21];
    result__[ 3   ] = XL__[3] - ModelPars[2];
    result__[ 4   ] = XL__[4] - ModelPars[22];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"boundaryConditions_eval",5);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  farmer_problem::DboundaryConditionsDx_numRows() const
  { return 5; }

  integer
  farmer_problem::DboundaryConditionsDx_numCols() const
  { return 10; }

  integer
  farmer_problem::DboundaryConditionsDx_nnz() const
  { return 5; }

  void
  farmer_problem::DboundaryConditionsDx_pattern(
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
  farmer_problem::DboundaryConditionsDx_sparse(
    integer              i_segment_left,
    Q_const_pointer_type QL__,
    X_const_pointer_type XL__,
    integer              i_segment_right,
    Q_const_pointer_type QR__,
    X_const_pointer_type XR__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);

    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DboundaryConditionsDxp_sparse",5);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  farmer_problem::DboundaryConditionsDp_numRows() const
  { return 5; }

  integer
  farmer_problem::DboundaryConditionsDp_numCols() const
  { return 0; }

  integer
  farmer_problem::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  farmer_problem::DboundaryConditionsDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  farmer_problem::DboundaryConditionsDp_sparse(
    integer              i_segment_left,
    Q_const_pointer_type QL__,
    X_const_pointer_type XL__,
    integer              i_segment_right,
    Q_const_pointer_type QR__,
    X_const_pointer_type XR__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY

  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  farmer_problem::adjointBC_numEqns() const
  { return 10; }

  void
  farmer_problem::adjointBC_eval(
    integer                  i_segment_left,
    Q_const_pointer_type     QL__,
    X_const_pointer_type     XL__,
    L_const_pointer_type     LL__,
    integer                  i_segment_right,
    Q_const_pointer_type     QR__,
    X_const_pointer_type     XR__,
    L_const_pointer_type     LR__,
    P_const_pointer_type     P__,
    OMEGA_const_pointer_type _OMEGA,
    real_type                result__[]
  ) const {
    // mapping active omega to full omega
    integer   dim_omega_full = 5;
    real_type OMEGA__[5 ];
    alglin::zero( dim_omega_full, OMEGA__, 1 );
    for ( integer i = 0; i < numOMEGA(); ++i )
      OMEGA__[ omegaInvMap(i) ] = _OMEGA[i];

    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);

    result__[ 0   ] = OMEGA__[0] + LL__[0];
    result__[ 1   ] = OMEGA__[1] + LL__[1];
    result__[ 2   ] = OMEGA__[2] + LL__[2];
    result__[ 3   ] = OMEGA__[3] + LL__[3];
    result__[ 4   ] = OMEGA__[4] + LL__[4];
    result__[ 5   ] = -LR__[0];
    result__[ 6   ] = -LR__[1];
    result__[ 7   ] = -LR__[2];
    result__[ 8   ] = -LR__[3];
    result__[ 9   ] = -LR__[4];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"adjointBC_eval",10);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  farmer_problem::DadjointBCDx_numRows() const
  { return 10; }

  integer
  farmer_problem::DadjointBCDx_numCols() const
  { return 10; }

  integer
  farmer_problem::DadjointBCDx_nnz() const
  { return 0; }

  void
  farmer_problem::DadjointBCDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  farmer_problem::DadjointBCDx_sparse(
    integer                  i_segment_left,
    Q_const_pointer_type     QL__,
    X_const_pointer_type     XL__,
    L_const_pointer_type     LL__,
    integer                  i_segment_right,
    Q_const_pointer_type     QR__,
    X_const_pointer_type     XR__,
    L_const_pointer_type     LR__,
    P_const_pointer_type     P__,
    OMEGA_const_pointer_type _OMEGA,
    real_type                result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  farmer_problem::DadjointBCDp_numRows() const
  { return 10; }

  integer
  farmer_problem::DadjointBCDp_numCols() const
  { return 0; }

  integer
  farmer_problem::DadjointBCDp_nnz() const
  { return 0; }

  void
  farmer_problem::DadjointBCDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  farmer_problem::DadjointBCDp_sparse(
    integer                  i_segment_left,
    Q_const_pointer_type     QL__,
    X_const_pointer_type     XL__,
    L_const_pointer_type     LL__,
    integer                  i_segment_right,
    Q_const_pointer_type     QR__,
    X_const_pointer_type     XR__,
    L_const_pointer_type     LR__,
    P_const_pointer_type     P__,
    OMEGA_const_pointer_type _OMEGA,
    real_type                result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: farmer_problem_Methods.cc
