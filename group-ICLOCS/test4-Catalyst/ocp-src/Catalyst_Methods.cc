/*-----------------------------------------------------------------------*\
 |  file: Catalyst_Methods.cc                                            |
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


#include "Catalyst.hh"
#include "Catalyst_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)



namespace CatalystDefine {

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  valueType
  Catalyst::penalties_eval(
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
    
    return 0;

  }

  valueType
  Catalyst::control_penalties_eval(
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
    
    return uControl(U__[iU_u], 0, 1);

  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  valueType
  Catalyst::lagrange_target(
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
    
    return 0;

  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  valueType
  Catalyst::mayer_target(
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
    
    return -1 + XR__[iX_x1] + XR__[iX_x2];

  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  indexType
  Catalyst::q_numEqns() const
  { return 1; }

  void
  Catalyst::q_eval(
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
  Catalyst::boundaryConditions_numEqns() const
  { return 2; }

  void
  Catalyst::boundaryConditions_eval(
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
    
    result__[ 0   ] = XL__[iX_x1] - ModelPars[iM_x1_i];
    result__[ 1   ] = XL__[iX_x2] - ModelPars[iM_x2_i];

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"boundaryConditions_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  Catalyst::DboundaryConditionsDx_numRows() const
  { return 2; }

  indexType
  Catalyst::DboundaryConditionsDx_numCols() const
  { return 4; }

  indexType
  Catalyst::DboundaryConditionsDx_nnz() const
  { return 2; }

  void
  Catalyst::DboundaryConditionsDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
  }

  void
  Catalyst::DboundaryConditionsDx_sparse(
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
  Catalyst::DboundaryConditionsDp_numRows() const
  { return 2; }

  indexType
  Catalyst::DboundaryConditionsDp_numCols() const
  { return 0; }

  indexType
  Catalyst::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  Catalyst::DboundaryConditionsDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::DboundaryConditionsDp_sparse(
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
  Catalyst::adjointBC_numEqns() const
  { return 4; }

  void
  Catalyst::adjointBC_eval(
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
    result__[ 2   ] = 1 - LR__[iL_lambda1__xo];
    result__[ 3   ] = 1 - LR__[iL_lambda2__xo];

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"adjointBC_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  Catalyst::DadjointBCDx_numRows() const
  { return 4; }

  indexType
  Catalyst::DadjointBCDx_numCols() const
  { return 4; }

  indexType
  Catalyst::DadjointBCDx_nnz() const
  { return 0; }

  void
  Catalyst::DadjointBCDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::DadjointBCDx_sparse(
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
  Catalyst::DadjointBCDp_numRows() const
  { return 4; }

  indexType
  Catalyst::DadjointBCDp_numCols() const
  { return 0; }

  indexType
  Catalyst::DadjointBCDp_nnz() const
  { return 0; }

  void
  Catalyst::DadjointBCDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::DadjointBCDp_sparse(
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
  Catalyst::rhs_ode_numEqns() const
  { return 2; }

  void
  Catalyst::rhs_ode_eval(
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
    
    valueType t1   =  U__[iU_u];
    valueType t2   =  X__[iX_x2];
    valueType t5   =  10 * t2 - X__[iX_x1];
    result__[ 0   ] = t5 * t1;
    result__[ 1   ] = -t5 * t1 - t2 * (1 - t1);

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"rhs_ode",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  Catalyst::Drhs_odeDx_numRows() const
  { return 2; }

  indexType
  Catalyst::Drhs_odeDx_numCols() const
  { return 2; }

  indexType
  Catalyst::Drhs_odeDx_nnz() const
  { return 4; }

  void
  Catalyst::Drhs_odeDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 0   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 1   ;
  }

  void
  Catalyst::Drhs_odeDx_sparse(
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
    
    valueType t1   =  U__[iU_u];
    result__[ 0   ] = -t1;
    result__[ 1   ] = 10 * t1;
    result__[ 2   ] = t1;
    result__[ 3   ] = -9 * result__[2] - 1;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDxp_sparse",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  Catalyst::Drhs_odeDp_numRows() const
  { return 2; }

  indexType
  Catalyst::Drhs_odeDp_numCols() const
  { return 0; }

  indexType
  Catalyst::Drhs_odeDp_nnz() const
  { return 0; }

  void
  Catalyst::Drhs_odeDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::Drhs_odeDp_sparse(
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
  Catalyst::Drhs_odeDu_numRows() const
  { return 2; }

  indexType
  Catalyst::Drhs_odeDu_numCols() const
  { return 1; }

  indexType
  Catalyst::Drhs_odeDu_nnz() const
  { return 2; }

  void
  Catalyst::Drhs_odeDu_pattern( indexType iIndex[], indexType jIndex[] ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 0   ;
  }

  void
  Catalyst::Drhs_odeDu_sparse(
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
    
    valueType t1   =  X__[iX_x2];
    valueType t3   =  X__[iX_x1];
    result__[ 0   ] = 10 * t1 - t3;
    result__[ 1   ] = t3 - 9 * t1;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDu_sparse",2);
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
  Catalyst::Hx_numEqns() const
  { return 2; }

  void
  Catalyst::Hx_eval(
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
    
    valueType t2   =  U__[iU_u];
    valueType t3   =  t2 * L__[iL_lambda1__xo];
    valueType t4   =  L__[iL_lambda2__xo];
    result__[ 0   ] = t2 * t4 - t3;
    result__[ 1   ] = 10 * t3 + (-9 * t2 - 1) * t4;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hx_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  Catalyst::DHxDx_numRows() const
  { return 2; }

  indexType
  Catalyst::DHxDx_numCols() const
  { return 2; }

  indexType
  Catalyst::DHxDx_nnz() const
  { return 0; }

  void
  Catalyst::DHxDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::DHxDx_sparse(
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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  Catalyst::DHxDp_numRows() const
  { return 2; }

  indexType
  Catalyst::DHxDp_numCols() const
  { return 0; }

  indexType
  Catalyst::DHxDp_nnz() const
  { return 0; }

  void
  Catalyst::DHxDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::DHxDp_sparse(
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
  Catalyst::Hu_numEqns() const
  { return 1; }

  void
  Catalyst::Hu_eval(
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
    
    valueType t2   =  X__[iX_x2];
    valueType t4   =  X__[iX_x1];
    result__[ 0   ] = (10 * t2 - t4) * L__[iL_lambda1__xo] + (t4 - 9 * t2) * L__[iL_lambda2__xo];

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hu_eval",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  Catalyst::DHuDx_numRows() const
  { return 1; }

  indexType
  Catalyst::DHuDx_numCols() const
  { return 2; }

  indexType
  Catalyst::DHuDx_nnz() const
  { return 2; }

  void
  Catalyst::DHuDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
  }

  void
  Catalyst::DHuDx_sparse(
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
    
    valueType t1   =  L__[iL_lambda1__xo];
    valueType t2   =  L__[iL_lambda2__xo];
    result__[ 0   ] = -t1 + t2;
    result__[ 1   ] = 10 * t1 - 9 * t2;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHuDx_sparse",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  Catalyst::DHuDp_numRows() const
  { return 1; }

  indexType
  Catalyst::DHuDp_numCols() const
  { return 0; }

  indexType
  Catalyst::DHuDp_nnz() const
  { return 0; }

  void
  Catalyst::DHuDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::DHuDp_sparse(
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
  Catalyst::Hp_numEqns() const
  { return 0; }

  void
  Catalyst::Hp_eval(
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
  Catalyst::DHpDp_numRows() const
  { return 0; }

  indexType
  Catalyst::DHpDp_numCols() const
  { return 0; }

  indexType
  Catalyst::DHpDp_nnz() const
  { return 0; }

  void
  Catalyst::DHpDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::DHpDp_sparse(
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
  Catalyst::g_numEqns() const
  { return 1; }

  void
  Catalyst::g_eval(
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
    
    valueType t2   =  X__[iX_x2];
    valueType t4   =  X__[iX_x1];
    valueType t12  =  ALIAS_uControl_D_1(U__[iU_u], 0, 1);
    result__[ 0   ] = (10 * t2 - t4) * L__[iL_lambda1__xo] + (t4 - 9 * t2) * L__[iL_lambda2__xo] + t12;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"g_eval",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  Catalyst::DgDxlp_numRows() const
  { return 1; }

  indexType
  Catalyst::DgDxlp_numCols() const
  { return 4; }

  indexType
  Catalyst::DgDxlp_nnz() const
  { return 4; }

  void
  Catalyst::DgDxlp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 0   ; jIndex[ 3  ] = 3   ;
  }

  void
  Catalyst::DgDxlp_sparse(
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
    
    valueType t1   =  L__[iL_lambda1__xo];
    valueType t2   =  L__[iL_lambda2__xo];
    result__[ 0   ] = -t1 + t2;
    result__[ 1   ] = 10 * t1 - 9 * t2;
    valueType t5   =  X__[iX_x2];
    valueType t7   =  X__[iX_x1];
    result__[ 2   ] = 10 * t5 - t7;
    result__[ 3   ] = t7 - 9 * t5;

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDxlp_sparse",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  indexType
  Catalyst::DgDu_numRows() const
  { return 1; }

  indexType
  Catalyst::DgDu_numCols() const
  { return 1; }

  indexType
  Catalyst::DgDu_nnz() const
  { return 1; }

  void
  Catalyst::DgDu_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
  }

  void
  Catalyst::DgDu_sparse(
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
    
    result__[ 0   ] = ALIAS_uControl_D_1_1(U__[iU_u], 0, 1);

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
  Catalyst::A_numRows() const
  { return 2; }

  indexType
  Catalyst::A_numCols() const
  { return 2; }

  indexType
  Catalyst::A_nnz() const
  { return 2; }

  void
  Catalyst::A_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
  }

  void
  Catalyst::A_sparse(
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
  Catalyst::eta_numEqns() const
  { return 2; }

  void
  Catalyst::eta_eval(
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
  Catalyst::DetaDx_numRows() const
  { return 2; }

  indexType
  Catalyst::DetaDx_numCols() const
  { return 2; }

  indexType
  Catalyst::DetaDx_nnz() const
  { return 0; }

  void
  Catalyst::DetaDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::DetaDx_sparse(
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
  Catalyst::DetaDp_numRows() const
  { return 2; }

  indexType
  Catalyst::DetaDp_numCols() const
  { return 0; }

  indexType
  Catalyst::DetaDp_nnz() const
  { return 0; }

  void
  Catalyst::DetaDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::DetaDp_sparse(
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
  Catalyst::nu_numEqns() const
  { return 2; }

  void
  Catalyst::nu_eval(
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
  Catalyst::DnuDx_numRows() const
  { return 2; }

  indexType
  Catalyst::DnuDx_numCols() const
  { return 2; }

  indexType
  Catalyst::DnuDx_nnz() const
  { return 0; }

  void
  Catalyst::DnuDx_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::DnuDx_sparse(
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
  Catalyst::DnuDp_numRows() const
  { return 2; }

  indexType
  Catalyst::DnuDp_numCols() const
  { return 0; }

  indexType
  Catalyst::DnuDp_nnz() const
  { return 0; }

  void
  Catalyst::DnuDp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {

  }

  void
  Catalyst::DnuDp_sparse(
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
  Catalyst::u_numEqns() const
  { return 1; }

  void
  Catalyst::u_eval(
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
      
      valueType t1   =  L__[iL_lambda1__xo];
      valueType t2   =  X__[iX_x1];
      valueType t4   =  X__[iX_x2];
      valueType t7   =  L__[iL_lambda2__xo];
      U__[ iU_u ] = uControl.solve(t2 * t1 - 10 * t4 * t1 - t2 * t7 + 9 * t4 * t7, 0, 1);

    #else
      u_standard_eval( i_segment, _Q, _X, _L, _P, _U );
    #endif

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(U__,"u_eval",1);
    #endif
  }

  void
  Catalyst::DuDxlp_full(
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
        
    DuDxlp(0, 0) = uControl.solve_rhs(L__[iL_lambda1__xo] * X__[iX_x1] - 10 * L__[iL_lambda1__xo] * X__[iX_x2] - L__[iL_lambda2__xo] * X__[iX_x1] + 9 * L__[iL_lambda2__xo] * X__[iX_x2], 0, 1) * (L__[iL_lambda1__xo] - L__[iL_lambda2__xo]);
    DuDxlp(0, 1) = uControl.solve_rhs(L__[iL_lambda1__xo] * X__[iX_x1] - 10 * L__[iL_lambda1__xo] * X__[iX_x2] - L__[iL_lambda2__xo] * X__[iX_x1] + 9 * L__[iL_lambda2__xo] * X__[iX_x2], 0, 1) * (-10 * L__[iL_lambda1__xo] + 9 * L__[iL_lambda2__xo]);
    DuDxlp(0, 2) = uControl.solve_rhs(L__[iL_lambda1__xo] * X__[iX_x1] - 10 * L__[iL_lambda1__xo] * X__[iX_x2] - L__[iL_lambda2__xo] * X__[iX_x1] + 9 * L__[iL_lambda2__xo] * X__[iX_x2], 0, 1) * (X__[iX_x1] - 10 * X__[iX_x2]);
    DuDxlp(0, 3) = uControl.solve_rhs(L__[iL_lambda1__xo] * X__[iX_x1] - 10 * L__[iL_lambda1__xo] * X__[iX_x2] - L__[iL_lambda2__xo] * X__[iX_x1] + 9 * L__[iL_lambda2__xo] * X__[iX_x2], 0, 1) * (9 * X__[iX_x2] - X__[iX_x1]);

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
  Catalyst::segmentLink_numEqns() const
  { return 0; }

  void
  Catalyst::segmentLink_eval(
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
  Catalyst::DsegmentLinkDxp_numRows() const
  { return 0; }

  indexType
  Catalyst::DsegmentLinkDxp_numCols() const
  { return 0; }

  indexType
  Catalyst::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  Catalyst::DsegmentLinkDxp_pattern(
    indexType iIndex[],
    indexType jIndex[]
  ) const {
    ASSERT(false,"NON IMPLEMENTATA");
  }

  void
  Catalyst::DsegmentLinkDxp_sparse(
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
  Catalyst::jump_numEqns() const
  { return 4; }

  void
  Catalyst::jump_eval(
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
  Catalyst::DjumpDxlp_numRows() const
  { return 4; }

  indexType
  Catalyst::DjumpDxlp_numCols() const
  { return 8; }

  indexType
  Catalyst::DjumpDxlp_nnz() const
  { return 8; }

  void
  Catalyst::DjumpDxlp_pattern(
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
  Catalyst::DjumpDxlp_sparse(
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
  Catalyst::u_guess_numEqns() const
  { return 1; }

  void
  Catalyst::u_guess_eval(
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
  Catalyst::u_check_if_admissible(
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
      
      uControl.check_range(U__[iU_u], 0, 1);

    } catch ( exception const & exc ) {
      DO_ERROR("Catalyst::u_check_if_admissible: " << exc.what());
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
  Catalyst::post_numEqns() const
  { return 0; }

  void
  Catalyst::post_eval(
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
  Catalyst::integrated_post_numEqns() const
  { return 0; }

  void
  Catalyst::integrated_post_eval(
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

// EOF: Catalyst_Methods.cc
