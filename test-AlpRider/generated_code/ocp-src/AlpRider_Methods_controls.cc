/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods_controls.cc                                   |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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


#include "AlpRider.hh"
#include "AlpRider_Pars.hh"

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
#pragma warning( disable : 4189 )
#endif

// map user defined functions and objects with macros
#define ALIAS_Ybound_DD(__t1) Ybound.DD( __t1)
#define ALIAS_Ybound_D(__t1) Ybound.D( __t1)


namespace AlpRiderDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  AlpRider::g_fun_eval(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_W];
    real_type t2   = XL__[iX_y1];
    real_type t3   = t2 * t2;
    real_type t4   = XL__[iX_y2];
    real_type t5   = t4 * t4;
    real_type t6   = XL__[iX_y3];
    real_type t7   = t6 * t6;
    real_type t8   = XL__[iX_y4];
    real_type t9   = t8 * t8;
    real_type t12  = UM__[0];
    real_type t13  = t12 * t12;
    real_type t15  = UM__[1];
    real_type t16  = t15 * t15;
    real_type t18  = LM__[0];
    real_type t22  = LM__[1];
    real_type t24  = 2 * t15;
    real_type t27  = LM__[2];
    real_type t32  = LM__[3];
    real_type t35  = 3 * t15;
    real_type t39  = q_lower(QL__[iQ_zeta]);
    real_type t41  = Ybound(t39 - t3 - t5 - t7 - t9);
    real_type t42  = XR__[iX_y1];
    real_type t43  = t42 * t42;
    real_type t44  = XR__[iX_y2];
    real_type t45  = t44 * t44;
    real_type t46  = XR__[iX_y3];
    real_type t47  = t46 * t46;
    real_type t48  = XR__[iX_y4];
    real_type t49  = t48 * t48;
    real_type t67  = q_lower(QR__[iQ_zeta]);
    real_type t69  = Ybound(t67 - t43 - t45 - t47 - t49);
    real_type result__ = (t3 + t5 + t7 + t9) * t1 + t13 / 50 + t16 / 50 + (-10 * t2 + t12 + t15) * t18 + (-2 * t4 + t12 + t24) * t22 + (-3 * t6 + 5 * t8 + t12 - t15) * t27 + (5 * t6 - 3 * t8 + t12 + t35) * t32 + t41 + (t43 + t45 + t47 + t49) * t1 + (-10 * t42 + t12 + t15) * t18 + (-2 * t44 + t12 + t24) * t22 + (-3 * t46 + 5 * t48 + t12 - t15) * t27 + (5 * t46 - 3 * t48 + t12 + t35) * t32 + t69;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer AlpRider::g_numEqns() const { return 2; }

  void
  AlpRider::g_eval(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = 2 * LM__[0];
    real_type t5   = LM__[1];
    real_type t8   = 2 * LM__[2];
    real_type t9   = LM__[3];
    result__[ 0   ] = UM__[0] / 25 + t4 + 2 * t5 + t8 + 2 * t9;
    result__[ 1   ] = UM__[1] / 25 + t4 + 4 * t5 - t8 + 6 * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DgDxlxlp_numRows() const { return 2; }
  integer AlpRider::DgDxlxlp_numCols() const { return 16; }
  integer AlpRider::DgDxlxlp_nnz()     const { return 16; }

  void
  AlpRider::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 12  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 13  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 14  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 15  ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 5   ;
    iIndex[10] = 1   ; jIndex[10] = 6   ;
    iIndex[11] = 1   ; jIndex[11] = 7   ;
    iIndex[12] = 1   ; jIndex[12] = 12  ;
    iIndex[13] = 1   ; jIndex[13] = 13  ;
    iIndex[14] = 1   ; jIndex[14] = 14  ;
    iIndex[15] = 1   ; jIndex[15] = 15  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DgDxlxlp_sparse(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1.0;
    result__[ 1   ] = 1.0;
    result__[ 2   ] = 1.0;
    result__[ 3   ] = 1.0;
    result__[ 4   ] = 1.0;
    result__[ 5   ] = 1.0;
    result__[ 6   ] = 1.0;
    result__[ 7   ] = 1.0;
    result__[ 8   ] = 1.0;
    result__[ 9   ] = 2.0;
    result__[ 10  ] = -1.0;
    result__[ 11  ] = 3.0;
    result__[ 12  ] = 1.0;
    result__[ 13  ] = 2.0;
    result__[ 14  ] = -1.0;
    result__[ 15  ] = 3.0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DgDu_numRows() const { return 2; }
  integer AlpRider::DgDu_numCols() const { return 2; }
  integer AlpRider::DgDu_nnz()     const { return 2; }

  void
  AlpRider::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DgDu_sparse(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1.0 / 0.25e2;
    result__[ 1   ] = 1.0 / 0.25e2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 2, i_segment );
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
  AlpRider::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t2   = LM__[1];
    real_type t3   = LM__[2];
    real_type t4   = LM__[3];
    U__[ iU_u1 ] = -50 * t1 - 50 * t2 - 50 * t3 - 50 * t4;
    U__[ iU_u2 ] = -50 * t1 - 100 * t2 + 50 * t3 - 150 * t4;
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 2 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  AlpRider::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = q_lower(Q__[iQ_zeta]);
    real_type t3   = X__[iX_y1];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_y2];
    real_type t6   = t5 * t5;
    real_type t7   = X__[iX_y3];
    real_type t8   = t7 * t7;
    real_type t9   = X__[iX_y4];
    real_type t10  = t9 * t9;
    real_type t12  = Ybound(t2 - t4 - t6 - t8 - t10);
    real_type t15  = U__[iU_u1];
    real_type t16  = U__[iU_u2];
    real_type t18  = pow(V__[0] + 10 * t3 - t15 - t16, 2);
    real_type t23  = pow(V__[1] + 2 * t5 - t15 - 2 * t16, 2);
    real_type t28  = pow(V__[2] + 3 * t7 - 5 * t9 - t15 + t16, 2);
    real_type t34  = pow(V__[3] - 5 * t7 + 3 * t9 - t15 - 3 * t16, 2);
    real_type result__ = t12 + t18 + t23 + t28 + t34;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer AlpRider::DmDu_numEqns() const { return 2; }

  void
  AlpRider::DmDu_eval(
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
    real_type t2   = 2 * V__[0];
    real_type t4   = 20 * X__[iX_y1];
    real_type t5   = U__[iU_u1];
    real_type t7   = U__[iU_u2];
    real_type t9   = V__[1];
    real_type t11  = X__[iX_y2];
    real_type t14  = 2 * V__[2];
    real_type t15  = X__[iX_y3];
    real_type t17  = X__[iX_y4];
    real_type t19  = V__[3];
    result__[ 0   ] = -t2 - t4 + 8 * t5 + 10 * t7 - 2 * t9 - 4 * t11 - t14 + 4 * t15 + 4 * t17 - 2 * t19;
    result__[ 1   ] = -t2 - t4 + 10 * t5 + 30 * t7 - 4 * t9 - 8 * t11 + t14 + 36 * t15 - 28 * t17 - 6 * t19;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DmDuu_numRows() const { return 2; }
  integer AlpRider::DmDuu_numCols() const { return 2; }
  integer AlpRider::DmDuu_nnz()     const { return 4; }

  void
  AlpRider::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }


  void
  AlpRider::DmDuu_sparse(
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
    result__[ 0   ] = 8;
    result__[ 1   ] = 10;
    result__[ 2   ] = 10;
    result__[ 3   ] = 30;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 4, i_segment );
  }

}

// EOF: AlpRider_Methods_controls.cc
