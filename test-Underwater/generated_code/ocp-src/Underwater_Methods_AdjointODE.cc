/*-----------------------------------------------------------------------*\
 |  file: Underwater_Methods_AdjointODE.cc                               |
 |                                                                       |
 |  version: 1.0   date 13/12/2021                                       |
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


#include "Underwater.hh"
#include "Underwater_Pars.hh"

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
#define ALIAS_u3Control_D_3(__t1, __t2, __t3) u3Control.D_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2(__t1, __t2, __t3) u3Control.D_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1(__t1, __t2, __t3) u3Control.D_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3_3(__t1, __t2, __t3) u3Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_3(__t1, __t2, __t3) u3Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_2(__t1, __t2, __t3) u3Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_3(__t1, __t2, __t3) u3Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_2(__t1, __t2, __t3) u3Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_1(__t1, __t2, __t3) u3Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace UnderwaterDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  Underwater::Hx_numEqns() const
  { return 6; }

  void
  Underwater::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_vz];
    real_type t5   = X__[iX_theta];
    real_type t6   = cos(t5);
    real_type t8   = X__[iX_vx];
    real_type t9   = sin(t5);
    real_type t14  = t2 * L__[iL_lambda2__xo];
    result__[ 2   ] = (t4 * t6 - t9 * t8) * t3 + (-t9 * t4 - t6 * t8) * t14;
    real_type t22  = t2 * L__[iL_lambda5__xo];
    real_type t23  = X__[iX_Omega];
    real_type t24  = ModelPars[iM_m1];
    real_type t26  = ModelPars[iM_m3];
    real_type t27  = 1.0 / t26;
    real_type t31  = t2 * L__[iL_lambda6__xo];
    real_type t32  = t26 - t24;
    real_type t35  = 1.0 / ModelPars[iM_inertia];
    result__[ 3   ] = t27 * t24 * t23 * t22 + t35 * t32 * t4 * t31 - t9 * t14 + t6 * t3;
    real_type t41  = t2 * L__[iL_lambda4__xo];
    real_type t43  = 1.0 / t24;
    result__[ 4   ] = -t43 * t26 * t23 * t41 + t35 * t32 * t8 * t31 + t6 * t14 + t9 * t3;
    result__[ 5   ] = t27 * t24 * t8 * t22 - t43 * t26 * t4 * t41 + t2 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DHxDx_numRows() const
  { return 6; }

  integer
  Underwater::DHxDx_numCols() const
  { return 6; }

  integer
  Underwater::DHxDx_nnz() const
  { return 11; }

  void
  Underwater::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 5   ; jIndex[9 ] = 3   ;
    iIndex[10] = 5   ; jIndex[10] = 4   ;
  }

  void
  Underwater::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_vz];
    real_type t5   = X__[iX_theta];
    real_type t6   = sin(t5);
    real_type t8   = X__[iX_vx];
    real_type t9   = cos(t5);
    real_type t14  = t2 * L__[iL_lambda2__xo];
    result__[ 0   ] = (-t6 * t4 - t9 * t8) * t3 + (-t9 * t4 + t6 * t8) * t14;
    result__[ 1   ] = -t9 * t14 - t6 * t3;
    result__[ 2   ] = -t6 * t14 + t9 * t3;
    result__[ 3   ] = result__[1];
    real_type t25  = ModelPars[iM_m3];
    real_type t26  = ModelPars[iM_m1];
    result__[ 4   ] = 1.0 / ModelPars[iM_inertia] * (t25 - t26) * t2 * L__[iL_lambda6__xo];
    result__[ 5   ] = 1.0 / t25 * t26 * t2 * L__[iL_lambda5__xo];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[4];
    result__[ 8   ] = -1.0 / t26 * t25 * t2 * L__[iL_lambda4__xo];
    result__[ 9   ] = result__[5];
    result__[ 10  ] = result__[8];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 11, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DHxDp_numRows() const
  { return 6; }

  integer
  Underwater::DHxDp_numCols() const
  { return 1; }

  integer
  Underwater::DHxDp_nnz() const
  { return 4; }

  void
  Underwater::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 3   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 4   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 5   ; jIndex[3 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_vz];
    real_type t3   = X__[iX_theta];
    real_type t4   = cos(t3);
    real_type t6   = X__[iX_vx];
    real_type t7   = sin(t3);
    real_type t11  = L__[iL_lambda2__xo];
    result__[ 0   ] = (t4 * t2 - t7 * t6) * t1 + (-t7 * t2 - t6 * t4) * t11;
    real_type t18  = L__[iL_lambda5__xo];
    real_type t19  = X__[iX_Omega];
    real_type t21  = ModelPars[iM_m1];
    real_type t22  = ModelPars[iM_m3];
    real_type t24  = 1.0 / t22 * t21;
    real_type t26  = L__[iL_lambda6__xo];
    real_type t31  = 1.0 / ModelPars[iM_inertia] * (t22 - t21);
    result__[ 1   ] = t24 * t19 * t18 + t31 * t2 * t26 + t4 * t1 - t7 * t11;
    real_type t35  = L__[iL_lambda4__xo];
    real_type t38  = 1.0 / t21 * t22;
    result__[ 2   ] = -t38 * t19 * t35 + t31 * t6 * t26 + t7 * t1 + t4 * t11;
    result__[ 3   ] = t24 * t6 * t18 - t38 * t2 * t35 + L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDp_sparse", 4, i_segment );
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
  Underwater::Hu_numEqns() const
  { return 3; }

  void
  Underwater::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    result__[ 0   ] = 1.0 / ModelPars[iM_m1] * t2 * L__[iL_lambda4__xo];
    result__[ 1   ] = 1.0 / ModelPars[iM_m3] * t2 * L__[iL_lambda5__xo];
    result__[ 2   ] = 1.0 / ModelPars[iM_inertia] * t2 * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DHuDx_numRows() const
  { return 3; }

  integer
  Underwater::DHuDx_numCols() const
  { return 6; }

  integer
  Underwater::DHuDx_nnz() const
  { return 0; }

  void
  Underwater::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DHuDp_numRows() const
  { return 3; }

  integer
  Underwater::DHuDp_numCols() const
  { return 1; }

  integer
  Underwater::DHuDp_nnz() const
  { return 3; }

  void
  Underwater::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda4__xo] / ModelPars[iM_m1];
    result__[ 1   ] = L__[iL_lambda5__xo] / ModelPars[iM_m3];
    result__[ 2   ] = L__[iL_lambda6__xo] / ModelPars[iM_inertia];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHuDp_sparse", 3, i_segment );
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
  Underwater::Hp_numEqns() const
  { return 1; }

  void
  Underwater::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_vx];
    real_type t3   = X__[iX_theta];
    real_type t4   = cos(t3);
    real_type t6   = X__[iX_vz];
    real_type t7   = sin(t3);
    real_type t17  = X__[iX_Omega];
    real_type t21  = ModelPars[iM_m1];
    real_type t22  = 1.0 / t21;
    real_type t25  = ModelPars[iM_m3];
    real_type t32  = 1.0 / t25;
    real_type t42  = 1.0 / ModelPars[iM_inertia];
    result__[ 0   ] = (t4 * t2 + t7 * t6) * L__[iL_lambda1__xo] + (-t7 * t2 + t4 * t6) * L__[iL_lambda2__xo] + t17 * L__[iL_lambda3__xo] + (-t22 * t25 * t17 * t6 + t22 * U__[iU_u1]) * L__[iL_lambda4__xo] + (t32 * t21 * t17 * t2 + t32 * U__[iU_u2]) * L__[iL_lambda5__xo] + (t42 * U__[iU_u3] + t42 * (t25 - t21) * t6 * t2) * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DHpDp_numRows() const
  { return 1; }

  integer
  Underwater::DHpDp_numCols() const
  { return 1; }

  integer
  Underwater::DHpDp_nnz() const
  { return 0; }

  void
  Underwater::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DHpDp_sparse(
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
  Underwater::eta_numEqns() const
  { return 6; }

  void
  Underwater::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    result__[ 4   ] = L__[iL_lambda5__xo];
    result__[ 5   ] = L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DetaDx_numRows() const
  { return 6; }

  integer
  Underwater::DetaDx_numCols() const
  { return 6; }

  integer
  Underwater::DetaDx_nnz() const
  { return 0; }

  void
  Underwater::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DetaDp_numRows() const
  { return 6; }

  integer
  Underwater::DetaDp_numCols() const
  { return 1; }

  integer
  Underwater::DetaDp_nnz() const
  { return 0; }

  void
  Underwater::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DetaDp_sparse(
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
  Underwater::nu_numEqns() const
  { return 6; }

  void
  Underwater::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    result__[ 5   ] = V__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DnuDx_numRows() const
  { return 6; }

  integer
  Underwater::DnuDx_numCols() const
  { return 6; }

  integer
  Underwater::DnuDx_nnz() const
  { return 0; }

  void
  Underwater::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DnuDp_numRows() const
  { return 6; }

  integer
  Underwater::DnuDp_numCols() const
  { return 1; }

  integer
  Underwater::DnuDp_nnz() const
  { return 0; }

  void
  Underwater::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: Underwater_Methods_AdjointODE.cc
