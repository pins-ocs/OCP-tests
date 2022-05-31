/*-----------------------------------------------------------------------*\
 |  file: Farmer_Methods_controls.cc                                     |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  Farmer::g_fun_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_w1];
    real_type t4   = XM__[0];
    real_type t6   = ModelPars[iM_w2];
    real_type t8   = XM__[1];
    real_type t10  = ModelPars[iM_w3];
    real_type t12  = XM__[2];
    real_type t14  = ModelPars[iM_w4];
    real_type t16  = XM__[4];
    real_type t19  = Ptot(QM__[0]);
    real_type t21  = pow(t4 / t2 + t8 / t6 + t12 / t10 + t16 / t14 - t19, 2);
    real_type t23  = t4 * t4;
    real_type t25  = t8 * t8;
    real_type t27  = t12 * t12;
    real_type t29  = t16 * t16;
    real_type t32  = UM__[0];
    real_type t33  = -t4 + t32;
    real_type t34  = t33 * t33;
    real_type t37  = UM__[1];
    real_type t38  = -t8 + t37;
    real_type t39  = t38 * t38;
    real_type t42  = UM__[2];
    real_type t43  = -t12 + t42;
    real_type t44  = t43 * t43;
    real_type t47  = UM__[3];
    real_type t48  = -t16 + t47;
    real_type t49  = t48 * t48;
    real_type t81  = x1__oControl(t32, -0.1e-2, 100);
    real_type t82  = x2__oControl(t37, -0.1e-2, 100);
    real_type t83  = x3__oControl(t42, -0.1e-2, 100);
    real_type t84  = x4__oControl(t47, -0.1e-2, 100);
    real_type t86  = LimitX2X4(t8 + t16 - 0.12e0);
    real_type result__ = t21 * ModelPars[iM_wP] + t2 * t23 + t25 * t6 + t10 * t27 + t14 * t29 + t34 * ModelPars[iM_wJ1] + t39 * ModelPars[iM_wJ2] + t44 * ModelPars[iM_wJ3] + t49 * ModelPars[iM_wJ4] + 1.0 / ModelPars[iM_tau__1] * t33 * LM__[0] + 1.0 / ModelPars[iM_tau__2] * t38 * LM__[1] + 1.0 / ModelPars[iM_tau__3] * t43 * LM__[2] - 1.0 / ModelPars[iM_tau__4] * (-t12 + t16) * LM__[3] + 1.0 / ModelPars[iM_tau__5] * t48 * LM__[4] + t81 + t82 + t83 + t84 + t86;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Farmer::g_numEqns() const { return 4; }

  void
  Farmer::g_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = UM__[0];
    real_type t11  = ALIAS_x1__oControl_D_1(t3, -0.1e-2, 100);
    result__[ 0   ] = 2 * (-XM__[0] + t3) * ModelPars[iM_wJ1] + LM__[0] / ModelPars[iM_tau__1] + t11;
    real_type t14  = UM__[1];
    real_type t22  = ALIAS_x2__oControl_D_1(t14, -0.1e-2, 100);
    result__[ 1   ] = 2 * (-XM__[1] + t14) * ModelPars[iM_wJ2] + LM__[1] / ModelPars[iM_tau__2] + t22;
    real_type t25  = UM__[2];
    real_type t33  = ALIAS_x3__oControl_D_1(t25, -0.1e-2, 100);
    result__[ 2   ] = 2 * (-XM__[2] + t25) * ModelPars[iM_wJ3] + LM__[2] / ModelPars[iM_tau__3] + t33;
    real_type t36  = UM__[3];
    real_type t44  = ALIAS_x4__oControl_D_1(t36, -0.1e-2, 100);
    result__[ 3   ] = 2 * (-XM__[4] + t36) * ModelPars[iM_wJ4] + LM__[4] / ModelPars[iM_tau__5] + t44;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Farmer::DgDxlxlp_numRows() const { return 4; }
  integer Farmer::DgDxlxlp_numCols() const { return 20; }
  integer Farmer::DgDxlxlp_nnz()     const { return 16; }

  void
  Farmer::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 10  ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 15  ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 11  ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 16  ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 7   ;
    iIndex[10] = 2   ; jIndex[10] = 12  ;
    iIndex[11] = 2   ; jIndex[11] = 17  ;
    iIndex[12] = 3   ; jIndex[12] = 4   ;
    iIndex[13] = 3   ; jIndex[13] = 9   ;
    iIndex[14] = 3   ; jIndex[14] = 14  ;
    iIndex[15] = 3   ; jIndex[15] = 19  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -0.10e1 * ModelPars[iM_wJ1];
    result__[ 1   ] = 0.5e0 / ModelPars[iM_tau__1];
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = -0.10e1 * ModelPars[iM_wJ2];
    result__[ 5   ] = 0.5e0 / ModelPars[iM_tau__2];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = result__[5];
    result__[ 8   ] = -0.10e1 * ModelPars[iM_wJ3];
    result__[ 9   ] = 0.5e0 / ModelPars[iM_tau__3];
    result__[ 10  ] = result__[8];
    result__[ 11  ] = result__[9];
    result__[ 12  ] = -0.10e1 * ModelPars[iM_wJ4];
    result__[ 13  ] = 0.5e0 / ModelPars[iM_tau__5];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[13];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Farmer::DgDu_numRows() const { return 4; }
  integer Farmer::DgDu_numCols() const { return 4; }
  integer Farmer::DgDu_nnz()     const { return 4; }

  void
  Farmer::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = ALIAS_x1__oControl_D_1_1(UM__[0], -0.1e-2, 100);
    result__[ 0   ] = 2 * ModelPars[iM_wJ1] + t4;
    real_type t8   = ALIAS_x2__oControl_D_1_1(UM__[1], -0.1e-2, 100);
    result__[ 1   ] = 2 * ModelPars[iM_wJ2] + t8;
    real_type t12  = ALIAS_x3__oControl_D_1_1(UM__[2], -0.1e-2, 100);
    result__[ 2   ] = 2 * ModelPars[iM_wJ3] + t12;
    real_type t16  = ALIAS_x4__oControl_D_1_1(UM__[3], -0.1e-2, 100);
    result__[ 3   ] = 2 * ModelPars[iM_wJ4] + t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 4, i_segment );
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/

  void
  Farmer::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    UTILS_ERROR(
      "Farmer::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  Farmer::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_x1__o];
    real_type t2   = x1__oControl(t1, -0.1e-2, 100);
    real_type t3   = U__[iU_x2__o];
    real_type t4   = x2__oControl(t3, -0.1e-2, 100);
    real_type t5   = U__[iU_x3__o];
    real_type t6   = x3__oControl(t5, -0.1e-2, 100);
    real_type t7   = U__[iU_x4__o];
    real_type t8   = x4__oControl(t7, -0.1e-2, 100);
    real_type t9   = X__[iX_x2];
    real_type t10  = X__[iX_x4];
    real_type t12  = LimitX2X4(t9 + t10 - 0.12e0);
    real_type t20  = pow(V__[0] + 1.0 / ModelPars[iM_tau__1] * (X__[iX_x1] - t1), 2);
    real_type t27  = pow(V__[1] + 1.0 / ModelPars[iM_tau__2] * (t9 - t3), 2);
    real_type t29  = X__[iX_x3];
    real_type t35  = pow(V__[2] + 1.0 / ModelPars[iM_tau__3] * (t29 - t5), 2);
    real_type t42  = pow(V__[3] + 1.0 / ModelPars[iM_tau__4] * (-t29 + t10), 2);
    real_type t49  = pow(V__[4] + 1.0 / ModelPars[iM_tau__5] * (t10 - t7), 2);
    real_type result__ = t2 + t4 + t6 + t8 + t12 + t20 + t27 + t35 + t42 + t49;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Farmer::DmDu_numEqns() const { return 4; }

  void
  Farmer::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_x1__o];
    real_type t2   = ALIAS_x1__oControl_D_1(t1, -0.1e-2, 100);
    real_type t7   = 1.0 / ModelPars[iM_tau__1];
    result__[ 0   ] = t2 - 2 * t7 * (V__[0] + t7 * (X__[iX_x1] - t1));
    real_type t12  = U__[iU_x2__o];
    real_type t13  = ALIAS_x2__oControl_D_1(t12, -0.1e-2, 100);
    real_type t18  = 1.0 / ModelPars[iM_tau__2];
    result__[ 1   ] = t13 - 2 * t18 * (V__[1] + t18 * (X__[iX_x2] - t12));
    real_type t23  = U__[iU_x3__o];
    real_type t24  = ALIAS_x3__oControl_D_1(t23, -0.1e-2, 100);
    real_type t29  = 1.0 / ModelPars[iM_tau__3];
    result__[ 2   ] = t24 - 2 * t29 * (V__[2] + t29 * (X__[iX_x3] - t23));
    real_type t34  = U__[iU_x4__o];
    real_type t35  = ALIAS_x4__oControl_D_1(t34, -0.1e-2, 100);
    real_type t40  = 1.0 / ModelPars[iM_tau__5];
    result__[ 3   ] = t35 - 2 * t40 * (V__[4] + t40 * (X__[iX_x4] - t34));
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Farmer::DmDuu_numRows() const { return 4; }
  integer Farmer::DmDuu_numCols() const { return 4; }
  integer Farmer::DmDuu_nnz()     const { return 4; }

  void
  Farmer::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }


  void
  Farmer::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ALIAS_x1__oControl_D_1_1(U__[iU_x1__o], -0.1e-2, 100);
    real_type t4   = ModelPars[iM_tau__1] * ModelPars[iM_tau__1];
    result__[ 0   ] = t2 + 2 / t4;
    real_type t8   = ALIAS_x2__oControl_D_1_1(U__[iU_x2__o], -0.1e-2, 100);
    real_type t10  = ModelPars[iM_tau__2] * ModelPars[iM_tau__2];
    result__[ 1   ] = t8 + 2 / t10;
    real_type t14  = ALIAS_x3__oControl_D_1_1(U__[iU_x3__o], -0.1e-2, 100);
    real_type t16  = ModelPars[iM_tau__3] * ModelPars[iM_tau__3];
    result__[ 2   ] = t14 + 2 / t16;
    real_type t20  = ALIAS_x4__oControl_D_1_1(U__[iU_x4__o], -0.1e-2, 100);
    real_type t22  = ModelPars[iM_tau__5] * ModelPars[iM_tau__5];
    result__[ 3   ] = t20 + 2 / t22;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 4, i_segment );
  }

}

// EOF: Farmer_Methods_controls.cc
