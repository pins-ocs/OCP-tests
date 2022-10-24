/*-----------------------------------------------------------------------*\
 |  file: MaximumAscent_Methods_controls.cc                              |
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


#include "MaximumAscent.hh"
#include "MaximumAscent_Pars.hh"

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


namespace MaximumAscentDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  MaximumAscent::g_fun_eval(
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
    real_type t3   = tf(ModelPars[iM_days]);
    real_type t4   = eta(t3);
    real_type t5   = t4 * LM__[0];
    real_type t6   = XL__[iX_u];
    real_type t8   = LM__[1];
    real_type t9   = XL__[iX_v];
    real_type t10  = t9 * t9;
    real_type t11  = XL__[iX_r];
    real_type t12  = 1.0 / t11;
    real_type t14  = t11 * t11;
    real_type t18  = Tbar(t3);
    real_type t20  = ModelPars[iM_mdot] * t3;
    real_type t23  = ModelPars[iM_m0];
    real_type t26  = 1.0 / (-QL__[iQ_zeta] * t20 + t23) * t18;
    real_type t27  = UM__[0];
    real_type t28  = sin(t27);
    real_type t32  = LM__[2];
    real_type t34  = t12 * t9;
    real_type t36  = cos(t27);
    real_type t41  = t4 * LM__[3];
    real_type t43  = XR__[iX_u];
    real_type t45  = XR__[iX_v];
    real_type t46  = t45 * t45;
    real_type t47  = XR__[iX_r];
    real_type t48  = 1.0 / t47;
    real_type t50  = t47 * t47;
    real_type t58  = 1.0 / (-QR__[iQ_zeta] * t20 + t23) * t18;
    real_type t63  = t48 * t45;
    real_type result__ = t6 * t5 + ((t12 * t10 - 1.0 / t14) * t4 + t28 * t26) * t8 + (-t34 * t6 * t4 + t36 * t26) * t32 + t34 * t41 + t43 * t5 + ((t48 * t46 - 1.0 / t50) * t4 + t28 * t58) * t8 + (-t63 * t43 * t4 + t36 * t58) * t32 + t63 * t41;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer MaximumAscent::g_numEqns() const { return 1; }

  void
  MaximumAscent::g_eval(
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
    real_type t2   = tf(ModelPars[iM_days]);
    real_type t3   = Tbar(t2);
    real_type t5   = UM__[0];
    real_type t6   = sin(t5);
    real_type t9   = cos(t5);
    real_type t12  = (t6 * LM__[2] - t9 * LM__[1]) * t3;
    real_type t14  = ModelPars[iM_mdot] * t2;
    real_type t17  = ModelPars[iM_m0];
    result__[ 0   ] = 1.0 / (QL__[iQ_zeta] * t14 - t17) * t12 + 1.0 / (QR__[iQ_zeta] * t14 - t17) * t12;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DgDxlxlp_numRows() const { return 1; }
  integer MaximumAscent::DgDxlxlp_numCols() const { return 16; }
  integer MaximumAscent::DgDxlxlp_nnz()     const { return 4; }

  void
  MaximumAscent::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 5   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 13  ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 14  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::DgDxlxlp_sparse(
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
    real_type t2   = tf(ModelPars[iM_days]);
    real_type t3   = Tbar(t2);
    real_type t4   = UM__[0];
    real_type t5   = cos(t4);
    real_type t6   = t5 * t3;
    real_type t8   = ModelPars[iM_mdot] * t2;
    real_type t11  = ModelPars[iM_m0];
    real_type t13  = 1.0 / (QL__[iQ_zeta] * t8 - t11);
    real_type t19  = 1.0 / (QR__[iQ_zeta] * t8 - t11);
    result__[ 0   ] = -0.5e0 * t13 * t6 - 0.5e0 * t19 * t6;
    real_type t22  = sin(t4);
    real_type t23  = t22 * t3;
    result__[ 1   ] = 0.5e0 * t13 * t23 + 0.5e0 * t19 * t23;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DgDu_numRows() const { return 1; }
  integer MaximumAscent::DgDu_numCols() const { return 1; }
  integer MaximumAscent::DgDu_nnz()     const { return 1; }

  void
  MaximumAscent::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::DgDu_sparse(
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
    real_type t2   = tf(ModelPars[iM_days]);
    real_type t3   = Tbar(t2);
    real_type t5   = UM__[0];
    real_type t6   = cos(t5);
    real_type t9   = sin(t5);
    real_type t12  = (t6 * LM__[2] + t9 * LM__[1]) * t3;
    real_type t14  = ModelPars[iM_mdot] * t2;
    real_type t17  = ModelPars[iM_m0];
    result__[ 0   ] = 1.0 / (QL__[iQ_zeta] * t14 - t17) * t12 + 1.0 / (QR__[iQ_zeta] * t14 - t17) * t12;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 1, i_segment );
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
  MaximumAscent::u_eval_analytic(
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
    U__[ iU_alpha ] = arctan2__xo(-LM__[1], -LM__[2]);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 1 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  MaximumAscent::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = tf(ModelPars[iM_days]);
    real_type t4   = eta(t3);
    real_type t6   = X__[iX_u] * t4;
    real_type t8   = pow(V__[0] - t6, 2);
    real_type t10  = X__[iX_v];
    real_type t11  = t10 * t10;
    real_type t12  = X__[iX_r];
    real_type t13  = 1.0 / t12;
    real_type t15  = t12 * t12;
    real_type t19  = Tbar(t3);
    real_type t27  = 1.0 / (-Q__[iQ_zeta] * ModelPars[iM_mdot] * t3 + ModelPars[iM_m0]) * t19;
    real_type t28  = U__[iU_alpha];
    real_type t29  = sin(t28);
    real_type t32  = pow(V__[1] - (t13 * t11 - 1.0 / t15) * t4 - t29 * t27, 2);
    real_type t36  = cos(t28);
    real_type t39  = pow(t13 * t10 * t6 - t36 * t27 + V__[2], 2);
    real_type t44  = pow(-t13 * t10 * t4 + V__[3], 2);
    real_type result__ = t8 + t32 + t39 + t44;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer MaximumAscent::DmDu_numEqns() const { return 1; }

  void
  MaximumAscent::DmDu_eval(
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
    real_type t3   = tf(ModelPars[iM_days]);
    real_type t4   = eta(t3);
    real_type t5   = X__[iX_v];
    real_type t6   = t5 * t5;
    real_type t7   = X__[iX_r];
    real_type t8   = 1.0 / t7;
    real_type t10  = t7 * t7;
    real_type t14  = Tbar(t3);
    real_type t21  = 1.0 / (-Q__[iQ_zeta] * ModelPars[iM_mdot] * t3 + ModelPars[iM_m0]);
    real_type t22  = t21 * t14;
    real_type t23  = U__[iU_alpha];
    real_type t24  = sin(t23);
    real_type t28  = cos(t23);
    result__[ 0   ] = -2 * t28 * t21 * t14 * (V__[1] - (t8 * t6 - 1.0 / t10) * t4 - t24 * t22) + 2 * t24 * t21 * t14 * (t8 * t5 * X__[iX_u] * t4 - t28 * t22 + V__[2]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DmDuu_numRows() const { return 1; }
  integer MaximumAscent::DmDuu_numCols() const { return 1; }
  integer MaximumAscent::DmDuu_nnz()     const { return 1; }

  void
  MaximumAscent::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  MaximumAscent::DmDuu_sparse(
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
    real_type t2   = tf(ModelPars[iM_days]);
    real_type t3   = Tbar(t2);
    real_type t4   = t3 * t3;
    real_type t10  = -Q__[iQ_zeta] * ModelPars[iM_mdot] * t2 + ModelPars[iM_m0];
    real_type t11  = t10 * t10;
    real_type t13  = 1.0 / t11 * t4;
    real_type t14  = U__[iU_alpha];
    real_type t15  = cos(t14);
    real_type t16  = t15 * t15;
    real_type t19  = eta(t2);
    real_type t20  = X__[iX_v];
    real_type t21  = t20 * t20;
    real_type t22  = X__[iX_r];
    real_type t23  = 1.0 / t22;
    real_type t25  = t22 * t22;
    real_type t29  = 1.0 / t10;
    real_type t30  = t29 * t3;
    real_type t31  = sin(t14);
    real_type t37  = t31 * t31;
    result__[ 0   ] = 2 * t16 * t13 + 2 * t31 * t29 * t3 * (V__[1] - (t23 * t21 - 1.0 / t25) * t19 - t31 * t30) + 2 * t37 * t13 + 2 * t15 * t29 * t3 * (t23 * t20 * X__[iX_u] * t19 - t15 * t30 + V__[2]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: MaximumAscent_Methods_controls.cc
