/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Methods_AdjointODE.cc                                |
 |                                                                       |
 |  version: 1.0   date 16/11/2021                                       |
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


#include "Crossroad.hh"
#include "Crossroad_Pars.hh"

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
#define ALIAS_VelBound_DD(__t1) VelBound.DD( __t1)
#define ALIAS_VelBound_D(__t1) VelBound.D( __t1)
#define ALIAS_AccBound_DD(__t1) AccBound.DD( __t1)
#define ALIAS_AccBound_D(__t1) AccBound.D( __t1)
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_jerkControl_D_3(__t1, __t2, __t3) jerkControl.D_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2(__t1, __t2, __t3) jerkControl.D_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1(__t1, __t2, __t3) jerkControl.D_1( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_3_3(__t1, __t2, __t3) jerkControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_3(__t1, __t2, __t3) jerkControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_2(__t1, __t2, __t3) jerkControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_3(__t1, __t2, __t3) jerkControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_2(__t1, __t2, __t3) jerkControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_1(__t1, __t2, __t3) jerkControl.D_1_1( __t1, __t2, __t3)


namespace CrossroadDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  Crossroad::Hx_numEqns() const
  { return 4; }

  void
  Crossroad::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_a];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t5   = 1.0 / t4;
    real_type t7   = X__[iX_v];
    real_type t8   = t7 * t7;
    real_type t9   = t8 * t8;
    real_type t10  = X__[iX_s];
    real_type t11  = kappa(t10);
    real_type t12  = t11 * t11;
    real_type t15  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t16  = 1.0 / t15;
    real_type t19  = ALIAS_AccBound_D(-t16 * t12 * t9 - t5 * t2 + 1);
    real_type t22  = kappa_D(t10);
    result__[ 0   ] = -2 * t22 * t16 * t11 * t9 * t19;
    real_type t31  = ALIAS_VelBound_D(t7);
    real_type t32  = L__[iL_lambda1__xo];
    real_type t33  = X__[iX_Ts];
    result__[ 1   ] = -4 * t16 * t12 * t8 * t7 * t19 + t33 * t32 + t31;
    real_type t38  = L__[iL_lambda2__xo];
    result__[ 2   ] = -2 * t5 * t1 * t19 + t33 * t38;
    real_type t40  = ALIAS_Tpositive_D(t33);
    real_type t43  = U__[iU_jerk];
    real_type t44  = t43 * t43;
    result__[ 3   ] = t1 * t38 + t7 * t32 + t43 * L__[iL_lambda3__xo] + t44 * ModelPars[iM_wJ] + t40 + ModelPars[iM_wT];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DHxDx_numRows() const
  { return 4; }

  integer
  Crossroad::DHxDx_numCols() const
  { return 4; }

  integer
  Crossroad::DHxDx_nnz() const
  { return 14; }

  void
  Crossroad::DHxDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 2   ;
    iIndex[10] = 2   ; jIndex[10] = 3   ;
    iIndex[11] = 3   ; jIndex[11] = 1   ;
    iIndex[12] = 3   ; jIndex[12] = 2   ;
    iIndex[13] = 3   ; jIndex[13] = 3   ;
  }

  void
  Crossroad::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t3   = X__[iX_s];
    real_type t4   = kappa_DD(t3);
    real_type t5   = kappa(t3);
    real_type t7   = kappa_D(t3);
    real_type t8   = t7 * t7;
    real_type t11  = X__[iX_a];
    real_type t12  = t11 * t11;
    real_type t14  = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t15  = 1.0 / t14;
    real_type t17  = X__[iX_v];
    real_type t18  = t17 * t17;
    real_type t19  = t18 * t18;
    real_type t20  = t5 * t5;
    real_type t22  = 1.0 / t2;
    real_type t24  = -t22 * t20 * t19 - t15 * t12 + 1;
    real_type t25  = ALIAS_AccBound_D(t24);
    real_type t29  = ALIAS_AccBound_DD(t24);
    real_type t34  = t2 * t2;
    real_type t35  = 1.0 / t34;
    result__[ 0   ] = 4 * t35 * t19 * (-t25 * (t5 * t4 + t8) * t2 / 2 + t19 * t29 * t20 * t8);
    real_type t38  = t18 * t17;
    result__[ 1   ] = 8 * t35 * (t19 * t29 * t20 - t2 * t25) * t38 * t5 * t7;
    real_type t47  = t15 * t11 * t29;
    result__[ 2   ] = 4 * t7 * t22 * t5 * t19 * t47;
    result__[ 3   ] = result__[1];
    real_type t54  = t20 * t20;
    real_type t62  = ALIAS_VelBound_DD(t17);
    result__[ 4   ] = 16 * t35 * t54 * t19 * t18 * t29 - 12 * t22 * t20 * t18 * t25 + t62;
    result__[ 5   ] = 8 * t22 * t20 * t38 * t47;
    result__[ 6   ] = L__[iL_lambda1__xo];
    result__[ 7   ] = result__[2];
    result__[ 8   ] = result__[5];
    real_type t67  = t14 * t14;
    result__[ 9   ] = 4 / t67 * t12 * t29 - 2 * t15 * t25;
    result__[ 10  ] = L__[iL_lambda2__xo];
    result__[ 11  ] = result__[6];
    result__[ 12  ] = result__[10];
    result__[ 13  ] = ALIAS_Tpositive_DD(X__[iX_Ts]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 14, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DHxDp_numRows() const
  { return 4; }

  integer
  Crossroad::DHxDp_numCols() const
  { return 0; }

  integer
  Crossroad::DHxDp_nnz() const
  { return 0; }

  void
  Crossroad::DHxDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
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
  Crossroad::Hu_numEqns() const
  { return 1; }

  void
  Crossroad::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_Ts] * (2 * U__[iU_jerk] * ModelPars[iM_wJ] + L__[iL_lambda3__xo]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DHuDx_numRows() const
  { return 1; }

  integer
  Crossroad::DHuDx_numCols() const
  { return 4; }

  integer
  Crossroad::DHuDx_nnz() const
  { return 1; }

  void
  Crossroad::DHuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 2 * U__[iU_jerk] * ModelPars[iM_wJ] + L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DHuDp_numRows() const
  { return 1; }

  integer
  Crossroad::DHuDp_numCols() const
  { return 0; }

  integer
  Crossroad::DHuDp_nnz() const
  { return 0; }

  void
  Crossroad::DHuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
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
  Crossroad::Hp_numEqns() const
  { return 0; }

  void
  Crossroad::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DHpDp_numRows() const
  { return 0; }

  integer
  Crossroad::DHpDp_numCols() const
  { return 0; }

  integer
  Crossroad::DHpDp_nnz() const
  { return 0; }

  void
  Crossroad::DHpDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
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
  Crossroad::eta_numEqns() const
  { return 4; }

  void
  Crossroad::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DetaDx_numRows() const
  { return 4; }

  integer
  Crossroad::DetaDx_numCols() const
  { return 4; }

  integer
  Crossroad::DetaDx_nnz() const
  { return 0; }

  void
  Crossroad::DetaDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DetaDp_numRows() const
  { return 4; }

  integer
  Crossroad::DetaDp_numCols() const
  { return 0; }

  integer
  Crossroad::DetaDp_nnz() const
  { return 0; }

  void
  Crossroad::DetaDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DetaDp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
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
  Crossroad::nu_numEqns() const
  { return 4; }

  void
  Crossroad::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DnuDx_numRows() const
  { return 4; }

  integer
  Crossroad::DnuDx_numCols() const
  { return 4; }

  integer
  Crossroad::DnuDx_nnz() const
  { return 0; }

  void
  Crossroad::DnuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DnuDp_numRows() const
  { return 4; }

  integer
  Crossroad::DnuDp_numCols() const
  { return 0; }

  integer
  Crossroad::DnuDp_nnz() const
  { return 0; }

  void
  Crossroad::DnuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

}

// EOF: Crossroad_Methods_AdjointODE.cc
