/*-----------------------------------------------------------------------*\
 |  file: Farmer_Methods.cc                                              |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
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


#include "Farmer.hh"
#include "Farmer_Pars.hh"

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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ModelPars[10];
    real_type t3   = 1.0 / t2;
    real_type t4   = X__[0];
    real_type t6   = ModelPars[11];
    real_type t7   = 1.0 / t6;
    real_type t8   = X__[1];
    real_type t10  = ModelPars[12];
    real_type t11  = 1.0 / t10;
    real_type t12  = X__[2];
    real_type t14  = ModelPars[13];
    real_type t15  = 1.0 / t14;
    real_type t16  = X__[4];
    real_type t18  = ModelPars[3];
    real_type t19  = ModelPars[4];
    real_type t20  = Q__[0];
    real_type t32  = (t4 * t3 + t8 * t7 + t12 * t11 + t16 * t15 - 1.0 / (-t19 + t18) * (ModelPars[0] * (t18 - t19 + t20 - 1) - (t20 - 1) * ModelPars[1])) * ModelPars[18];
    result__[ 0   ] = 2 * t3 * t32 + 2 * t4 * t2 - 2 * (-t4 + U__[0]) * ModelPars[14] - L__[0] / ModelPars[5];
    real_type t47  = ALIAS_LimitX2X4_D(0.12e0 - t8 - t16);
    result__[ 1   ] = -t47 + 2 * t7 * t32 + 2 * t8 * t6 - 2 * (-t8 + U__[1]) * ModelPars[15] - L__[1] / ModelPars[6];
    real_type t77  = L__[3] / ModelPars[8];
    result__[ 2   ] = 2 * t11 * t32 + 2 * t12 * t10 - 2 * (-t12 + U__[2]) * ModelPars[16] - L__[2] / ModelPars[7] + t77;
    result__[ 3   ] = 0;
    result__[ 4   ] = -t47 + 2 * t15 * t32 + 2 * t16 * t14 - 2 * (-t16 + U__[3]) * ModelPars[17] - t77 - L__[4] / ModelPars[9];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hx_eval",5);
    #endif
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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 2 * ModelPars[14] * (-X__[0] + U__[0]) + L__[0] / ModelPars[5];
    result__[ 1   ] = 2 * ModelPars[15] * (-X__[1] + U__[1]) + L__[1] / ModelPars[6];
    result__[ 2   ] = 2 * ModelPars[16] * (-X__[2] + U__[2]) + L__[2] / ModelPars[7];
    result__[ 3   ] = 2 * ModelPars[17] * (-X__[4] + U__[3]) + L__[4] / ModelPars[9];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hu_eval",4);
    #endif
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
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 4   ;
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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = -2 * ModelPars[14];
    result__[ 1   ] = -2 * ModelPars[15];
    result__[ 2   ] = -2 * ModelPars[16];
    result__[ 3   ] = -2 * ModelPars[17];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHuDx_sparse",4);
    #endif
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
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hp_eval",0);
    #endif
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

// EOF: Farmer_Methods.cc
