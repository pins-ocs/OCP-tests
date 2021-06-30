/*-----------------------------------------------------------------------*\
 |  file: Farmer_Methods_AdjointODE.cc                                   |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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


#include "Farmer.hh"
#include "Farmer_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

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


namespace FarmerDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  Farmer::Hx_numEqns() const
  { return 5; }

  void
  Farmer::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_w1];
    real_type t3   = 1.0 / t2;
    real_type t4   = X__[iX_x1];
    real_type t6   = ModelPars[iM_w2];
    real_type t7   = 1.0 / t6;
    real_type t8   = X__[iX_x2];
    real_type t10  = ModelPars[iM_w3];
    real_type t11  = 1.0 / t10;
    real_type t12  = X__[iX_x3];
    real_type t14  = ModelPars[iM_w4];
    real_type t15  = 1.0 / t14;
    real_type t16  = X__[iX_x4];
    real_type t18  = ModelPars[iM_t1];
    real_type t19  = ModelPars[iM_t2];
    real_type t20  = Q__[iQ_zeta];
    real_type t32  = (t4 * t3 + t8 * t7 + t12 * t11 + t16 * t15 - 1.0 / (-t19 + t18) * (ModelPars[iM_P1] * (t18 - t19 + t20 - 1) - (t20 - 1) * ModelPars[iM_P2])) * ModelPars[iM_wP];
    result__[ 0   ] = 2 * t3 * t32 + 2 * t4 * t2 - 2 * (-t4 + U__[iU_x1__o]) * ModelPars[iM_wJ1] - L__[iL_lambda1__xo] / ModelPars[iM_tau__1];
    real_type t47  = ALIAS_LimitX2X4_D(0.12e0 - t8 - t16);
    result__[ 1   ] = -t47 + 2 * t7 * t32 + 2 * t8 * t6 - 2 * (-t8 + U__[iU_x2__o]) * ModelPars[iM_wJ2] - L__[iL_lambda2__xo] / ModelPars[iM_tau__2];
    real_type t77  = L__[iL_lambda4__xo] / ModelPars[iM_tau__4];
    result__[ 2   ] = 2 * t11 * t32 + 2 * t12 * t10 - 2 * (-t12 + U__[iU_x3__o]) * ModelPars[iM_wJ3] - L__[iL_lambda3__xo] / ModelPars[iM_tau__3] + t77;
    result__[ 3   ] = 0;
    result__[ 4   ] = -t47 + 2 * t15 * t32 + 2 * t16 * t14 - 2 * (-t16 + U__[iU_x4__o]) * ModelPars[iM_wJ4] - t77 - L__[iL_lambda5__xo] / ModelPars[iM_tau__5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DHxDx_numRows() const
  { return 5; }

  integer
  Farmer::DHxDx_numCols() const
  { return 5; }

  integer
  Farmer::DHxDx_nnz() const
  { return 16; }

  void
  Farmer::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 4   ;
    iIndex[12] = 4   ; jIndex[12] = 0   ;
    iIndex[13] = 4   ; jIndex[13] = 1   ;
    iIndex[14] = 4   ; jIndex[14] = 2   ;
    iIndex[15] = 4   ; jIndex[15] = 4   ;
  }

  void
  Farmer::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_wP];
    real_type t2   = ModelPars[iM_w1];
    real_type t3   = t2 * t2;
    result__[ 0   ] = 2 / t3 * t1 + 2 * t2 + 2 * ModelPars[iM_wJ1];
    real_type t8   = ModelPars[iM_w2];
    real_type t9   = 1.0 / t8;
    real_type t11  = 1.0 / t2;
    result__[ 1   ] = 2 * t11 * t9 * t1;
    real_type t13  = ModelPars[iM_w3];
    real_type t14  = 1.0 / t13;
    real_type t15  = t14 * t1;
    result__[ 2   ] = 2 * t11 * t15;
    real_type t17  = ModelPars[iM_w4];
    real_type t19  = 1.0 / t17 * t1;
    result__[ 3   ] = 2 * t11 * t19;
    result__[ 4   ] = result__[1];
    real_type t24  = ALIAS_LimitX2X4_DD(0.12e0 - X__[iX_x2] - X__[iX_x4]);
    real_type t25  = t8 * t8;
    result__[ 5   ] = t24 + 2 / t25 * t1 + 2 * t8 + 2 * ModelPars[iM_wJ2];
    result__[ 6   ] = 2 * t9 * t15;
    result__[ 7   ] = 2 * t9 * t19 + t24;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    real_type t35  = t13 * t13;
    result__[ 10  ] = 2 / t35 * t1 + 2 * t13 + 2 * ModelPars[iM_wJ3];
    result__[ 11  ] = 2 * t14 * t19;
    result__[ 12  ] = result__[3];
    result__[ 13  ] = result__[7];
    result__[ 14  ] = result__[11];
    real_type t41  = t17 * t17;
    result__[ 15  ] = t24 + 2 / t41 * t1 + 2 * t17 + 2 * ModelPars[iM_wJ4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DHxDp_numRows() const
  { return 5; }

  integer
  Farmer::DHxDp_numCols() const
  { return 0; }

  integer
  Farmer::DHxDp_nnz() const
  { return 0; }

  void
  Farmer::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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

  integer
  Farmer::Hu_numEqns() const
  { return 4; }

  void
  Farmer::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_x1__o];
    real_type t2   = ALIAS_x1__oControl_D_1(t1, -0.1e-2, 100);
    result__[ 0   ] = t2 + 2 * (-X__[iX_x1] + t1) * ModelPars[iM_wJ1] + L__[iL_lambda1__xo] / ModelPars[iM_tau__1];
    real_type t12  = U__[iU_x2__o];
    real_type t13  = ALIAS_x2__oControl_D_1(t12, -0.1e-2, 100);
    result__[ 1   ] = t13 + 2 * (-X__[iX_x2] + t12) * ModelPars[iM_wJ2] + L__[iL_lambda2__xo] / ModelPars[iM_tau__2];
    real_type t23  = U__[iU_x3__o];
    real_type t24  = ALIAS_x3__oControl_D_1(t23, -0.1e-2, 100);
    result__[ 2   ] = t24 + 2 * (-X__[iX_x3] + t23) * ModelPars[iM_wJ3] + L__[iL_lambda3__xo] / ModelPars[iM_tau__3];
    real_type t34  = U__[iU_x4__o];
    real_type t35  = ALIAS_x4__oControl_D_1(t34, -0.1e-2, 100);
    result__[ 3   ] = t35 + 2 * (-X__[iX_x4] + t34) * ModelPars[iM_wJ4] + L__[iL_lambda5__xo] / ModelPars[iM_tau__5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DHuDx_numRows() const
  { return 4; }

  integer
  Farmer::DHuDx_numCols() const
  { return 5; }

  integer
  Farmer::DHuDx_nnz() const
  { return 4; }

  void
  Farmer::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 4   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -2 * ModelPars[iM_wJ1];
    result__[ 1   ] = -2 * ModelPars[iM_wJ2];
    result__[ 2   ] = -2 * ModelPars[iM_wJ3];
    result__[ 3   ] = -2 * ModelPars[iM_wJ4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DHuDp_numRows() const
  { return 4; }

  integer
  Farmer::DHuDp_numCols() const
  { return 0; }

  integer
  Farmer::DHuDp_nnz() const
  { return 0; }

  void
  Farmer::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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

  integer
  Farmer::Hp_numEqns() const
  { return 0; }

  void
  Farmer::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DHpDp_numRows() const
  { return 0; }

  integer
  Farmer::DHpDp_numCols() const
  { return 0; }

  integer
  Farmer::DHpDp_nnz() const
  { return 0; }

  void
  Farmer::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/
  integer
  Farmer::eta_numEqns() const
  { return 5; }

  void
  Farmer::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    result__[ 4   ] = L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DetaDx_numRows() const
  { return 5; }

  integer
  Farmer::DetaDx_numCols() const
  { return 5; }

  integer
  Farmer::DetaDx_nnz() const
  { return 0; }

  void
  Farmer::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DetaDp_numRows() const
  { return 5; }

  integer
  Farmer::DetaDp_numCols() const
  { return 0; }

  integer
  Farmer::DetaDp_nnz() const
  { return 0; }

  void
  Farmer::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DetaDp_sparse(
    NodeType2 const    & NODE__,
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
  Farmer::nu_numEqns() const
  { return 5; }

  void
  Farmer::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DnuDx_numRows() const
  { return 5; }

  integer
  Farmer::DnuDx_numCols() const
  { return 5; }

  integer
  Farmer::DnuDx_nnz() const
  { return 0; }

  void
  Farmer::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DnuDp_numRows() const
  { return 5; }

  integer
  Farmer::DnuDp_numCols() const
  { return 0; }

  integer
  Farmer::DnuDp_nnz() const
  { return 0; }

  void
  Farmer::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: Farmer_Methods_AdjointODE.cc
