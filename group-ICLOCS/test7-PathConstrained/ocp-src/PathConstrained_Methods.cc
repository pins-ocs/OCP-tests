/*-----------------------------------------------------------------------*\
 |  file: PathConstrained_Methods.cc                                     |
 |                                                                       |
 |  version: 1.0   date 17/8/2018                                        |
 |                                                                       |
 |  Copyright (C) 2018                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "PathConstrained.hh"
#include "PathConstrained_Pars.hh"

using namespace std;
using namespace MechatronixCommon;

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
#define ALIAS_x2bound_DD(__t1) x2bound.DD( __t1)
#define ALIAS_x2bound_D(__t1) x2bound.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)



namespace PathConstrainedDefine {

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  valueType
  PathConstrained::penalties_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    U_const_pointer_type _U,
    P_const_pointer_type _P
  ) const {

    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    valueType t3   =  pow(Q__[iQ_zeta] - 0.5e0, 2);
    return x2bound(8 * t3 - 0.5e0 - X__[iX_x2]);

  }

  valueType
  PathConstrained::control_penalties_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    U_const_pointer_type _U,
    P_const_pointer_type _P
  ) const {

    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    return uControl(U__[iU_u], -20, 20);

  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  valueType
  PathConstrained::lagrange_target(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    U_const_pointer_type _U,
    P_const_pointer_type _P
  ) const {

    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    valueType t2   =  U__[iU_u] * U__[iU_u];
    valueType t5   =  X__[iX_x1] * X__[iX_x1];
    valueType t7   =  X__[iX_x2] * X__[iX_x2];
    return 0.5e-2 * t2 + t5 + t7;

  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  valueType
  PathConstrained::mayer_target(
    indexType            i_segment_left,
    Q_const_pointer_type _QL,
    X_const_pointer_type _XL,
    indexType            i_segment_right,
    Q_const_pointer_type _QR,
    X_const_pointer_type _XR,
    P_const_pointer_type _P
  ) const {

    valueConstPointer QL__ = _QL.pointer();
    valueConstPointer XL__ = _XL.pointer();
    valueConstPointer QR__ = _QR.pointer();
    valueConstPointer XR__ = _XR.pointer();
    valueConstPointer P__  = _P.pointer();
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    
    return 0;

  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  indexType
  PathConstrained::q_numEqns() const
  { return 1; }

  void
  PathConstrained::q_eval(
    indexType           i_node,
    indexType           i_segment,
    valueConstReference s,
    Q_pointer_type      _result
  ) const {

    valuePointer result__ = _result.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    result__[ 0   ] = s;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"q_eval",1);
    #endif
  }

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

  indexType
  PathConstrained::boundaryConditions_numEqns() const
  { return 2; }

  void
  PathConstrained::boundaryConditions_eval(
    indexType            i_segment_left,
    Q_const_pointer_type _QL,
    X_const_pointer_type _XL,
    indexType            i_segment_right,
    Q_const_pointer_type _QR,
    X_const_pointer_type _XR,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer QL__ = _QL.pointer();
    valueConstPointer XL__ = _XL.pointer();
    valueConstPointer QR__ = _QR.pointer();
    valueConstPointer XR__ = _XR.pointer();
    valueConstPointer P__  = _P.pointer();
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    
    result__[ 0   ] = XL__[iX_x1];
    result__[ 1   ] = XL__[iX_x2] + 1;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"boundaryConditions_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DboundaryConditionsDx_numRows() const
  { return 2; }

  indexType
  PathConstrained::DboundaryConditionsDx_numCols() const
  { return 4; }

  indexType
  PathConstrained::DboundaryConditionsDx_nnz() const
  { return 2; }

  void
  PathConstrained::DboundaryConditionsDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
  }

  void
  PathConstrained::DboundaryConditionsDx_sparse(
    indexType            i_segment_left,
    Q_const_pointer_type _QL,
    X_const_pointer_type _XL,
    indexType            i_segment_right,
    Q_const_pointer_type _QR,
    X_const_pointer_type _XR,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer QL__ = _QL.pointer();
    valueConstPointer XL__ = _XL.pointer();
    valueConstPointer QR__ = _QR.pointer();
    valueConstPointer XR__ = _XR.pointer();
    valueConstPointer P__  = _P.pointer();
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DboundaryConditionsDxp_sparse",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DboundaryConditionsDp_numRows() const
  { return 2; }

  indexType
  PathConstrained::DboundaryConditionsDp_numCols() const
  { return 0; }

  indexType
  PathConstrained::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  PathConstrained::DboundaryConditionsDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::DboundaryConditionsDp_sparse(
    indexType            i_segment_left,
    Q_const_pointer_type _QL,
    X_const_pointer_type _XL,
    indexType            i_segment_right,
    Q_const_pointer_type _QR,
    X_const_pointer_type _XR,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    // EMPTY
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::adjointBC_numEqns() const
  { return 4; }

  void
  PathConstrained::adjointBC_eval(
    indexType                i_segment_left,
    Q_const_pointer_type     _QL,
    X_const_pointer_type     _XL,
    L_const_pointer_type     _LL,
    indexType                i_segment_right,
    Q_const_pointer_type     _QR,
    X_const_pointer_type     _XR,
    L_const_pointer_type     _LR,
    P_const_pointer_type     _P,
    OMEGA_const_pointer_type _OMEGA,
    valueType                result__[]
  ) const {

    valueConstPointer QL__ = _QL.pointer();
    valueConstPointer XL__ = _XL.pointer();
    valueConstPointer LL__ = _LL.pointer();
    valueConstPointer QR__ = _QR.pointer();
    valueConstPointer XR__ = _XR.pointer();
    valueConstPointer LR__ = _LR.pointer();
    valueConstPointer P__  = _P.pointer();

    // mapping active omega to full omega
    indexType dim_omega_full = 2;
    valueType OMEGA__[2 ];
    alglin::zero( dim_omega_full, OMEGA__, 1 );
    for ( indexType i = 0; i < numOMEGA(); ++i )
      OMEGA__[ omegaInvMap(i) ] = _OMEGA[i];


    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);

    
    result__[ 0   ] = OMEGA__[0] + LL__[iL_lambda1__xo];
    result__[ 1   ] = OMEGA__[1] + LL__[iL_lambda2__xo];
    result__[ 2   ] = -LR__[iL_lambda1__xo];
    result__[ 3   ] = -LR__[iL_lambda2__xo];

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"adjointBC_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DadjointBCDx_numRows() const
  { return 4; }

  indexType
  PathConstrained::DadjointBCDx_numCols() const
  { return 4; }

  indexType
  PathConstrained::DadjointBCDx_nnz() const
  { return 0; }

  void
  PathConstrained::DadjointBCDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::DadjointBCDx_sparse(
    indexType                i_segment_left,
    Q_const_pointer_type     _QL,
    X_const_pointer_type     _XL,
    L_const_pointer_type     _LL,
    indexType                i_segment_right,
    Q_const_pointer_type     _QR,
    X_const_pointer_type     _XR,
    L_const_pointer_type     _LR,
    P_const_pointer_type     _P,
    OMEGA_const_pointer_type _OMEGA,
    valueType                result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DadjointBCDp_numRows() const
  { return 4; }

  indexType
  PathConstrained::DadjointBCDp_numCols() const
  { return 0; }

  indexType
  PathConstrained::DadjointBCDp_nnz() const
  { return 0; }

  void
  PathConstrained::DadjointBCDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::DadjointBCDp_sparse(
    indexType                i_segment_left,
    Q_const_pointer_type     _QL,
    X_const_pointer_type     _XL,
    L_const_pointer_type     _LL,
    indexType                i_segment_right,
    Q_const_pointer_type     _QR,
    X_const_pointer_type     _XR,
    L_const_pointer_type     _LR,
    P_const_pointer_type     _P,
    OMEGA_const_pointer_type _OMEGA,
    valueType                result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  indexType
  PathConstrained::rhs_ode_numEqns() const
  { return 2; }

  void
  PathConstrained::rhs_ode_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    result__[ 0   ] = X__[iX_x2];
    result__[ 1   ] = -result__[0] + U__[iU_u];

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"rhs_ode",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::Drhs_odeDx_numRows() const
  { return 2; }

  indexType
  PathConstrained::Drhs_odeDx_numCols() const
  { return 2; }

  indexType
  PathConstrained::Drhs_odeDx_nnz() const
  { return 2; }

  void
  PathConstrained::Drhs_odeDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 1   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
  }

  void
  PathConstrained::Drhs_odeDx_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    result__[ 0   ] = 1;
    result__[ 1   ] = -1;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDxp_sparse",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::Drhs_odeDp_numRows() const
  { return 2; }

  indexType
  PathConstrained::Drhs_odeDp_numCols() const
  { return 0; }

  indexType
  PathConstrained::Drhs_odeDp_nnz() const
  { return 0; }

  void
  PathConstrained::Drhs_odeDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::Drhs_odeDp_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::Drhs_odeDu_numRows() const
  { return 2; }

  indexType
  PathConstrained::Drhs_odeDu_numCols() const
  { return 1; }

  indexType
  PathConstrained::Drhs_odeDu_nnz() const
  { return 1; }

  void
  PathConstrained::Drhs_odeDu_pattern( indexType iIndex[], indexType jIndex[] ) const {
    iIndex[ 0  ] = 1   ; jIndex[ 0  ] = 0   ;
  }

  void
  PathConstrained::Drhs_odeDu_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    result__[ 0   ] = 1;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDu_sparse",1);
    #endif
  }

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  indexType
  PathConstrained::Hx_numEqns() const
  { return 2; }

  void
  PathConstrained::Hx_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    V_const_pointer_type _V,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer V__ = _V.pointer();
    valueConstPointer L__ = _L.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    result__[ 0   ] = 2 * X__[iX_x1];
    valueType t4   =  pow(Q__[iQ_zeta] - 0.5e0, 2);
    valueType t6   =  X__[iX_x2];
    valueType t8   =  ALIAS_x2bound_D(8 * t4 - 0.5e0 - t6);
    result__[ 1   ] = -t8 + 2 * t6 + L__[iL_lambda1__xo] - L__[iL_lambda2__xo];

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hx_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DHxDx_numRows() const
  { return 2; }

  indexType
  PathConstrained::DHxDx_numCols() const
  { return 2; }

  indexType
  PathConstrained::DHxDx_nnz() const
  { return 2; }

  void
  PathConstrained::DHxDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
  }

  void
  PathConstrained::DHxDx_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    V_const_pointer_type _V,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer V__ = _V.pointer();
    valueConstPointer L__ = _L.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    result__[ 0   ] = 2;
    valueType t3   =  pow(Q__[iQ_zeta] - 0.5e0, 2);
    valueType t7   =  ALIAS_x2bound_DD(8 * t3 - 0.5e0 - X__[iX_x2]);
    result__[ 1   ] = t7 + 2;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHxDx_sparse",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DHxDp_numRows() const
  { return 2; }

  indexType
  PathConstrained::DHxDp_numCols() const
  { return 0; }

  indexType
  PathConstrained::DHxDp_nnz() const
  { return 0; }

  void
  PathConstrained::DHxDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::DHxDp_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    V_const_pointer_type _V,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  indexType
  PathConstrained::Hu_numEqns() const
  { return 1; }

  void
  PathConstrained::Hu_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer L__ = _L.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    result__[ 0   ] = 0.10e-1 * U__[iU_u] + L__[iL_lambda2__xo];

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hu_eval",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DHuDx_numRows() const
  { return 1; }

  indexType
  PathConstrained::DHuDx_numCols() const
  { return 2; }

  indexType
  PathConstrained::DHuDx_nnz() const
  { return 0; }

  void
  PathConstrained::DHuDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::DHuDx_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DHuDp_numRows() const
  { return 1; }

  indexType
  PathConstrained::DHuDp_numCols() const
  { return 0; }

  indexType
  PathConstrained::DHuDp_nnz() const
  { return 0; }

  void
  PathConstrained::DHuDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::DHuDp_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_ __
   | | |_| | '_ \
   | |  _  | |_) |
   | |_| |_| .__/
   |       |_|
  \*/

  indexType
  PathConstrained::Hp_numEqns() const
  { return 0; }

  void
  PathConstrained::Hp_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    V_const_pointer_type _V,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer V__ = _V.pointer();
    valueConstPointer L__ = _L.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hp_eval",0);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DHpDp_numRows() const
  { return 0; }

  indexType
  PathConstrained::DHpDp_numCols() const
  { return 0; }

  indexType
  PathConstrained::DHpDp_nnz() const
  { return 0; }

  void
  PathConstrained::DHpDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::DHpDp_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    V_const_pointer_type _V,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  indexType
  PathConstrained::g_numEqns() const
  { return 1; }

  void
  PathConstrained::g_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer L__ = _L.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    valueType t1   =  U__[iU_u];
    valueType t4   =  ALIAS_uControl_D_1(t1, -20, 20);
    result__[ 0   ] = 0.10e-1 * t1 + L__[iL_lambda2__xo] + t4;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"g_eval",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DgDxlp_numRows() const
  { return 1; }

  indexType
  PathConstrained::DgDxlp_numCols() const
  { return 4; }

  indexType
  PathConstrained::DgDxlp_nnz() const
  { return 1; }

  void
  PathConstrained::DgDxlp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 3   ;
  }

  void
  PathConstrained::DgDxlp_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer L__ = _L.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    result__[ 0   ] = 1;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDxlp_sparse",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DgDu_numRows() const
  { return 1; }

  indexType
  PathConstrained::DgDu_numCols() const
  { return 1; }

  indexType
  PathConstrained::DgDu_nnz() const
  { return 1; }

  void
  PathConstrained::DgDu_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
  }

  void
  PathConstrained::DgDu_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer L__ = _L.pointer();
    valueConstPointer U__ = _U.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    valueType t2   =  ALIAS_uControl_D_1_1(U__[iU_u], -20, 20);
    result__[ 0   ] = 0.10e-1 + t2;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDu_sparse",1);
    #endif
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  indexType
  PathConstrained::A_numRows() const
  { return 2; }

  indexType
  PathConstrained::A_numCols() const
  { return 2; }

  indexType
  PathConstrained::A_nnz() const
  { return 2; }

  void
  PathConstrained::A_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
  }

  void
  PathConstrained::A_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"A_sparse",2);
    #endif
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  indexType
  PathConstrained::eta_numEqns() const
  { return 2; }

  void
  PathConstrained::eta_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer L__ = _L.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"eta_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DetaDx_numRows() const
  { return 2; }

  indexType
  PathConstrained::DetaDx_numCols() const
  { return 2; }

  indexType
  PathConstrained::DetaDx_nnz() const
  { return 0; }

  void
  PathConstrained::DetaDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::DetaDx_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DetaDp_numRows() const
  { return 2; }

  indexType
  PathConstrained::DetaDp_numCols() const
  { return 0; }

  indexType
  PathConstrained::DetaDp_nnz() const
  { return 0; }

  void
  PathConstrained::DetaDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::DetaDp_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  indexType
  PathConstrained::nu_numEqns() const
  { return 2; }

  void
  PathConstrained::nu_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    V_const_pointer_type _V,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer V__ = _V.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"nu_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DnuDx_numRows() const
  { return 2; }

  indexType
  PathConstrained::DnuDx_numCols() const
  { return 2; }

  indexType
  PathConstrained::DnuDx_nnz() const
  { return 0; }

  void
  PathConstrained::DnuDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::DnuDx_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    V_const_pointer_type _V,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DnuDp_numRows() const
  { return 2; }

  indexType
  PathConstrained::DnuDp_numCols() const
  { return 0; }

  indexType
  PathConstrained::DnuDp_nnz() const
  { return 0; }

  void
  PathConstrained::DnuDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  PathConstrained::DnuDp_sparse(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    V_const_pointer_type _V,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    ___         _           _
   |   / __|___ _ _| |_ _ _ ___| |
   |  | (__/ _ \ ' \  _| '_/ _ \ |
   |   \___\___/_||_\__|_| \___/_|
  \*/

  indexType
  PathConstrained::u_numEqns() const
  { return 1; }

  void
  PathConstrained::u_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    P_const_pointer_type _P,
    U_pointer_type       _U
  ) const {
    valuePointer U__ = _U.pointer();
    #ifndef MECHATRONIX_U_ITERATIVE
      valueConstPointer X__ = _X.pointer();
      valueConstPointer L__ = _L.pointer();
      valueConstPointer P__ = _P.pointer();
      valueConstPointer Q__ = _Q.pointer();
      MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
      
      U__[ iU_u ] = 0;

    #else
      u_standard_eval( i_segment, _Q, _X, _L, _P, _U );
    #endif

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(U__,"u_eval",1);
    #endif
  }

  void
  PathConstrained::DuDxlp_full(
    indexType                  i_segment,
    Q_const_pointer_type       _Q,
    X_const_pointer_type       _X,
    L_const_pointer_type       _L,
    P_const_pointer_type       _P,
    U_const_pointer_type       _U,
    MatrixWrapper<valueType> & DuDxlp
  ) const {
    #ifndef MECHATRONIX_U_ITERATIVE
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer L__ = _L.pointer();
    valueConstPointer P__ = _P.pointer();
    valueConstPointer U__ = _U.pointer();
        
    DuDxlp(0, 0) = 0;
    DuDxlp(0, 1) = 0;
    DuDxlp(0, 2) = 0;
    DuDxlp(0, 3) = 0;

    #else
    DuDxlp_standard_full( i_segment, _Q, _X, _L, _P, _U, DuDxlp );
    #endif
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  indexType
  PathConstrained::segmentLink_numEqns() const
  { return 0; }

  void
  PathConstrained::segmentLink_eval(
    indexType            i_segment_left,
    Q_const_pointer_type qL,
    X_const_pointer_type xL,

    indexType            i_segment_right,
    Q_const_pointer_type qR,
    X_const_pointer_type xR,

    P_const_pointer_type p,

    valuePointer         segmentLink
  ) const {
    ASSERT(false,"NON IMPLEMENTATA");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DsegmentLinkDxp_numRows() const
  { return 0; }

  indexType
  PathConstrained::DsegmentLinkDxp_numCols() const
  { return 0; }

  indexType
  PathConstrained::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  PathConstrained::DsegmentLinkDxp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    ASSERT(false,"NON IMPLEMENTATA");
  }

  void
  PathConstrained::DsegmentLinkDxp_sparse(
    indexType            i_segment_left,
    Q_const_pointer_type qL,
    X_const_pointer_type xL,

    indexType            i_segment_right,
    Q_const_pointer_type qR,
    X_const_pointer_type xR,

    P_const_pointer_type p,

    valuePointer         DsegmentLinkDxp
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

  indexType
  PathConstrained::jump_numEqns() const
  { return 4; }

  void
  PathConstrained::jump_eval(
    indexType            i_segment_left,
    Q_const_pointer_type _QL,
    X_const_pointer_type _XL,
    L_const_pointer_type _LL,
    indexType            i_segment_right,
    Q_const_pointer_type _QR,
    X_const_pointer_type _XR,
    L_const_pointer_type _LR,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {

    valueConstPointer QL__ = _QL.pointer();
    valueConstPointer XL__ = _XL.pointer();
    valueConstPointer LL__ = _LL.pointer();
    valueConstPointer QR__ = _QR.pointer();
    valueConstPointer XR__ = _XR.pointer();
    valueConstPointer LR__ = _LR.pointer();
    valueConstPointer P__  = _P.pointer();
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    
    result__[ 0   ] = XR__[iX_x1] - XL__[iX_x1];
    result__[ 1   ] = XR__[iX_x2] - XL__[iX_x2];
    result__[ 2   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 3   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"jump_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::DjumpDxlp_numRows() const
  { return 4; }

  indexType
  PathConstrained::DjumpDxlp_numCols() const
  { return 8; }

  indexType
  PathConstrained::DjumpDxlp_nnz() const
  { return 8; }

  void
  PathConstrained::DjumpDxlp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 4   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 1   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 5   ;
    iIndex[ 4  ] = 2   ; jIndex[ 4  ] = 2   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 6   ;
    iIndex[ 6  ] = 3   ; jIndex[ 6  ] = 3   ;
    iIndex[ 7  ] = 3   ; jIndex[ 7  ] = 7   ;
  }

  void
  PathConstrained::DjumpDxlp_sparse(
    indexType            i_segment_left,
    Q_const_pointer_type _QL,
    X_const_pointer_type _XL,
    L_const_pointer_type _LL,
    indexType            i_segment_right,
    Q_const_pointer_type _QR,
    X_const_pointer_type _XR,
    L_const_pointer_type _LR,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
    valueConstPointer QL__ = _QL.pointer();
    valueConstPointer XL__ = _XL.pointer();
    valueConstPointer LL__ = _LL.pointer();
    valueConstPointer QR__ = _QR.pointer();
    valueConstPointer XR__ = _XR.pointer();
    valueConstPointer LR__ = _LR.pointer();
    valueConstPointer P__  = _P.pointer();
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

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DjumpDxlp_sparse",8);
    #endif
  }

  /*\
   |    ___
   |   / __|_  _ ___ ______
   |  | (_ | || / -_|_-<_-<
   |   \___|\_,_\___/__/__/
  \*/

  indexType
  PathConstrained::u_guess_numEqns() const
  { return 1; }

  void
  PathConstrained::u_guess_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    P_const_pointer_type _P,
    U_pointer_type       _U
  ) const {
    valueConstPointer X__ = _X.pointer();
    valueConstPointer L__ = _L.pointer();
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer P__ = _P.pointer();
    valuePointer      U__ = _U.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    std::fill( U__, U__+1, 0 );
    
    U__[ iU_u ] = 0;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(U__,"u_guess_eval",1);
    #endif
  }

  /*\
   |    ___ _           _
   |   / __| |_  ___ __| |__
   |  | (__| ' \/ -_) _| / /
   |   \___|_||_\___\__|_\_\
  \*/

  void
  PathConstrained::u_check_if_admissible(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P
  ) const {
    valueConstPointer U__ = _U.pointer();
    valueConstPointer X__ = _X.pointer();
    valueConstPointer L__ = _L.pointer();
    valueConstPointer Q__ = _Q.pointer();
    valueConstPointer P__ = _P.pointer();
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    try {
      
      uControl.check_range(U__[iU_u], -20, 20);

    } catch ( exception const & exc ) {
      DO_ERROR("PathConstrained::u_check_if_admissible: " << exc.what());
    }
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  indexType
  PathConstrained::post_numEqns() const
  { return 0; }

  void
  PathConstrained::post_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  PathConstrained::integrated_post_numEqns() const
  { return 0; }

  void
  PathConstrained::integrated_post_eval(
    indexType            i_segment,
    Q_const_pointer_type _Q,
    X_const_pointer_type _X,
    L_const_pointer_type _L,
    U_const_pointer_type _U,
    P_const_pointer_type _P,
    valueType            result__[]
  ) const {
  }

}

// EOF: PathConstrained_Methods.cc
