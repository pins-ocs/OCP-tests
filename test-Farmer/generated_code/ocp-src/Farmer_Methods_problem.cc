/*-----------------------------------------------------------------------*\
 |  file: Farmer_Methods_problem.cc                                      |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
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
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
   |
  \*/

  bool
  Farmer::penalties_check_cell(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    // midpoint
    real_type Q__[1], X__[5];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    X__[4] = (XL__[4]+XR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    bool res = true;
    res = res && LimitX2X4.check_range(X__[iX_x2] + X__[iX_x4] - 0.12e0, m_max_penalty_value);
    return res;
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  Farmer::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_w1];
    real_type t4   = X__[iX_x1];
    real_type t6   = ModelPars[iM_w2];
    real_type t8   = X__[iX_x2];
    real_type t10  = ModelPars[iM_w3];
    real_type t12  = X__[iX_x3];
    real_type t14  = ModelPars[iM_w4];
    real_type t16  = X__[iX_x4];
    real_type t19  = Ptot(Q__[iQ_zeta]);
    real_type t21  = pow(t4 / t2 + t8 / t6 + t12 / t10 + t16 / t14 - t19, 2);
    real_type t23  = t4 * t4;
    real_type t25  = t8 * t8;
    real_type t27  = t12 * t12;
    real_type t29  = t16 * t16;
    real_type t33  = -t4 + U__[iU_x1__o];
    real_type t34  = t33 * t33;
    real_type t38  = -t8 + U__[iU_x2__o];
    real_type t39  = t38 * t38;
    real_type t43  = -t12 + U__[iU_x3__o];
    real_type t44  = t43 * t43;
    real_type t48  = -t16 + U__[iU_x4__o];
    real_type t49  = t48 * t48;
    real_type result__ = t21 * ModelPars[iM_wP] + t2 * t23 + t25 * t6 + t10 * t27 + t14 * t29 + t34 * ModelPars[iM_wJ1] + t39 * ModelPars[iM_wJ2] + t44 * ModelPars[iM_wJ3] + t49 * ModelPars[iM_wJ4] + 1.0 / ModelPars[iM_tau__1] * t33 * L__[iL_lambda1__xo] + 1.0 / ModelPars[iM_tau__2] * t38 * L__[iL_lambda2__xo] + 1.0 / ModelPars[iM_tau__3] * t43 * L__[iL_lambda3__xo] - 1.0 / ModelPars[iM_tau__4] * (-t12 + t16) * L__[iL_lambda4__xo] + 1.0 / ModelPars[iM_tau__5] * t48 * L__[iL_lambda5__xo];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "H_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  Farmer::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JP_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  Farmer::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = x1__oControl(U__[iU_x1__o], -0.1e-2, 100);
    real_type t4   = x2__oControl(U__[iU_x2__o], -0.1e-2, 100);
    real_type t6   = x3__oControl(U__[iU_x3__o], -0.1e-2, 100);
    real_type t8   = x4__oControl(U__[iU_x4__o], -0.1e-2, 100);
    real_type result__ = t2 + t4 + t6 + t8;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JU_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  Farmer::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = LimitX2X4(X__[iX_x2] + X__[iX_x4] - 0.12e0);
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "LT_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  Farmer::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_w1];
    real_type t4   = X__[iX_x1];
    real_type t6   = ModelPars[iM_w2];
    real_type t8   = X__[iX_x2];
    real_type t10  = ModelPars[iM_w3];
    real_type t12  = X__[iX_x3];
    real_type t14  = ModelPars[iM_w4];
    real_type t16  = X__[iX_x4];
    real_type t19  = Ptot(Q__[iQ_zeta]);
    real_type t21  = pow(t4 / t2 + t8 / t6 + t12 / t10 + t16 / t14 - t19, 2);
    real_type t23  = t4 * t4;
    real_type t25  = t8 * t8;
    real_type t27  = t12 * t12;
    real_type t29  = t16 * t16;
    real_type t34  = pow(-t4 + U__[iU_x1__o], 2);
    real_type t39  = pow(-t8 + U__[iU_x2__o], 2);
    real_type t44  = pow(-t12 + U__[iU_x3__o], 2);
    real_type t49  = pow(-t16 + U__[iU_x4__o], 2);
    real_type result__ = t10 * t27 + t14 * t29 + t2 * t23 + t21 * ModelPars[iM_wP] + t25 * t6 + t34 * ModelPars[iM_wJ1] + t39 * ModelPars[iM_wJ2] + t44 * ModelPars[iM_wJ3] + t49 * ModelPars[iM_wJ4];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "lagrange_target(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  Farmer::mayer_target(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Farmer::DmayerDxxp_numEqns() const { return 10; }

  void
  Farmer::DmayerDxxp_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Farmer::D2mayerD2xxp_numRows() const { return 10; }
  integer Farmer::D2mayerD2xxp_numCols() const { return 10; }
  integer Farmer::D2mayerD2xxp_nnz()     const { return 0; }

  void
  Farmer::D2mayerD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Farmer::D2mayerD2xxp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer Farmer::DlagrangeDxup_numEqns() const { return 9; }

  void
  Farmer::DlagrangeDxup_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
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
    real_type t19  = Ptot(Q__[iQ_zeta]);
    real_type t21  = (t12 * t11 + t16 * t15 + t4 * t3 + t8 * t7 - t19) * ModelPars[iM_wP];
    real_type t27  = (-t4 + U__[iU_x1__o]) * ModelPars[iM_wJ1];
    result__[ 0   ] = 2 * t4 * t2 + 2 * t3 * t21 - 2 * t27;
    real_type t34  = (-t8 + U__[iU_x2__o]) * ModelPars[iM_wJ2];
    result__[ 1   ] = 2 * t7 * t21 + 2 * t8 * t6 - 2 * t34;
    real_type t41  = (-t12 + U__[iU_x3__o]) * ModelPars[iM_wJ3];
    result__[ 2   ] = 2 * t12 * t10 + 2 * t11 * t21 - 2 * t41;
    result__[ 3   ] = 0;
    real_type t48  = (-t16 + U__[iU_x4__o]) * ModelPars[iM_wJ4];
    result__[ 4   ] = 2 * t16 * t14 + 2 * t15 * t21 - 2 * t48;
    result__[ 5   ] = 2 * t27;
    result__[ 6   ] = 2 * t34;
    result__[ 7   ] = 2 * t41;
    result__[ 8   ] = 2 * t48;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxup_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Farmer::D2lagrangeD2xup_numRows() const { return 9; }
  integer Farmer::D2lagrangeD2xup_numCols() const { return 9; }
  integer Farmer::D2lagrangeD2xup_nnz()     const { return 28; }

  void
  Farmer::D2lagrangeD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 6   ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 4   ;
    iIndex[14] = 2   ; jIndex[14] = 7   ;
    iIndex[15] = 4   ; jIndex[15] = 0   ;
    iIndex[16] = 4   ; jIndex[16] = 1   ;
    iIndex[17] = 4   ; jIndex[17] = 2   ;
    iIndex[18] = 4   ; jIndex[18] = 4   ;
    iIndex[19] = 4   ; jIndex[19] = 8   ;
    iIndex[20] = 5   ; jIndex[20] = 0   ;
    iIndex[21] = 5   ; jIndex[21] = 5   ;
    iIndex[22] = 6   ; jIndex[22] = 1   ;
    iIndex[23] = 6   ; jIndex[23] = 6   ;
    iIndex[24] = 7   ; jIndex[24] = 2   ;
    iIndex[25] = 7   ; jIndex[25] = 7   ;
    iIndex[26] = 8   ; jIndex[26] = 4   ;
    iIndex[27] = 8   ; jIndex[27] = 8   ;
  }


  void
  Farmer::D2lagrangeD2xup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_wP];
    real_type t2   = ModelPars[iM_w1];
    real_type t3   = t2 * t2;
    real_type t6   = ModelPars[iM_wJ1];
    result__[ 0   ] = 2 / t3 * t1 + 2 * t2 + 2 * t6;
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
    real_type t21  = 2 * t6;
    result__[ 4   ] = -t21;
    result__[ 5   ] = result__[1];
    real_type t22  = t8 * t8;
    real_type t25  = ModelPars[iM_wJ2];
    result__[ 6   ] = 2 / t22 * t1 + 2 * t8 + 2 * t25;
    result__[ 7   ] = 2 * t9 * t15;
    result__[ 8   ] = 2 * t9 * t19;
    real_type t29  = 2 * t25;
    result__[ 9   ] = -t29;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t30  = t13 * t13;
    real_type t33  = ModelPars[iM_wJ3];
    result__[ 12  ] = 2 / t30 * t1 + 2 * t13 + 2 * t33;
    result__[ 13  ] = 2 * t14 * t19;
    real_type t36  = 2 * t33;
    result__[ 14  ] = -t36;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t37  = t17 * t17;
    real_type t40  = ModelPars[iM_wJ4];
    result__[ 18  ] = 2 / t37 * t1 + 2 * t17 + 2 * t40;
    real_type t42  = 2 * t40;
    result__[ 19  ] = -t42;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = t21;
    result__[ 22  ] = result__[9];
    result__[ 23  ] = t29;
    result__[ 24  ] = result__[14];
    result__[ 25  ] = t36;
    result__[ 26  ] = result__[19];
    result__[ 27  ] = t42;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2lagrangeD2xup_eval", 28, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  Farmer::q_numEqns() const
  { return 1; }

  void
  Farmer::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = s;
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer Farmer::segmentLink_numEqns() const { return 0; }

  void
  Farmer::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Farmer::DsegmentLinkDxp_numRows() const { return 0; }
  integer Farmer::DsegmentLinkDxp_numCols() const { return 0; }
  integer Farmer::DsegmentLinkDxp_nnz() const { return 0; }

  void
  Farmer::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            DsegmentLinkDxp[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer Farmer::jump_numEqns() const { return 10; }

  void
  Farmer::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XR__[iX_x1] - XL__[iX_x1];
    result__[ 1   ] = XR__[iX_x2] - XL__[iX_x2];
    result__[ 2   ] = XR__[iX_x3] - XL__[iX_x3];
    result__[ 3   ] = XR__[iX_res] - XL__[iX_res];
    result__[ 4   ] = XR__[iX_x4] - XL__[iX_x4];
    result__[ 5   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 6   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 7   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    result__[ 8   ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo];
    result__[ 9   ] = LR__[iL_lambda5__xo] - LL__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Farmer::DjumpDxlxlp_numRows() const { return 10; }
  integer Farmer::DjumpDxlxlp_numCols() const { return 20; }
  integer Farmer::DjumpDxlxlp_nnz()     const { return 20; }

  void
  Farmer::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 10  ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 11  ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 12  ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 13  ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 14  ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 15  ;
    iIndex[12] = 6   ; jIndex[12] = 6   ;
    iIndex[13] = 6   ; jIndex[13] = 16  ;
    iIndex[14] = 7   ; jIndex[14] = 7   ;
    iIndex[15] = 7   ; jIndex[15] = 17  ;
    iIndex[16] = 8   ; jIndex[16] = 8   ;
    iIndex[17] = 8   ; jIndex[17] = 18  ;
    iIndex[18] = 9   ; jIndex[18] = 9   ;
    iIndex[19] = 9   ; jIndex[19] = 19  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DjumpDxlxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
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
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 20, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer Farmer::post_numEqns() const { return 7; }

  void
  Farmer::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = x1__oControl(U__[iU_x1__o], -0.1e-2, 100);
    result__[ 1   ] = x2__oControl(U__[iU_x2__o], -0.1e-2, 100);
    result__[ 2   ] = x3__oControl(U__[iU_x3__o], -0.1e-2, 100);
    result__[ 3   ] = x4__oControl(U__[iU_x4__o], -0.1e-2, 100);
    real_type t5   = X__[iX_x2];
    real_type t6   = X__[iX_x4];
    result__[ 4   ] = LimitX2X4(t5 + t6 - 0.12e0);
    result__[ 5   ] = 1.0 / ModelPars[iM_w1] * X__[iX_x1] + t5 / ModelPars[iM_w2] + 1.0 / ModelPars[iM_w3] * X__[iX_x3] + t6 / ModelPars[iM_w4];
    result__[ 6   ] = Ptot(Q__[iQ_zeta]);
    Mechatronix::check_in_segment( result__, "post_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Farmer::integrated_post_numEqns() const { return 0; }

  void
  Farmer::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: Farmer_Methods_problem.cc
