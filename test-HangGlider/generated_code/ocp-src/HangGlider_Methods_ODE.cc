/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_ODE.cc                                      |
 |                                                                       |
 |  version: 1.0   date 3/4/2022                                         |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
#define ALIAS_Tbound_DD(__t1) Tbound.DD( __t1)
#define ALIAS_Tbound_D(__t1) Tbound.D( __t1)
#define ALIAS_cLControl_D_3(__t1, __t2, __t3) cLControl.D_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2(__t1, __t2, __t3) cLControl.D_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1(__t1, __t2, __t3) cLControl.D_1( __t1, __t2, __t3)
#define ALIAS_cLControl_D_3_3(__t1, __t2, __t3) cLControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_3(__t1, __t2, __t3) cLControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_2(__t1, __t2, __t3) cLControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_3(__t1, __t2, __t3) cLControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_2(__t1, __t2, __t3) cLControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_1(__t1, __t2, __t3) cLControl.D_1_1( __t1, __t2, __t3)


namespace HangGliderDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer HangGlider::rhs_ode_numEqns() const { return 4; }

  void
  HangGlider::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_vx];
    result__[ 0   ] = t2 * t1;
    real_type t3   = X__[iX_vy];
    result__[ 1   ] = t3 * t1;
    real_type t6   = 1.0 / ModelPars[iM_m] * t1;
    real_type t7   = X__[iX_x];
    real_type t8   = v(t7, t2, t3);
    real_type t9   = 1.0 / t8;
    real_type t11  = U__[iU_cL];
    real_type t12  = t11 * t11;
    real_type t16  = Dfun(t7, t2, t3);
    real_type t17  = t16 * (t12 * ModelPars[iM_c1] + ModelPars[iM_c0]);
    real_type t19  = Lfun(t7, t2, t3);
    real_type t20  = t19 * t11;
    real_type t21  = w(t7, t3);
    result__[ 2   ] = (-t2 * t17 - t21 * t20) * t9 * t6;
    result__[ 3   ] = (-t21 * t17 + t2 * t20) * t9 * t6 - ModelPars[iM_g] * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::Drhs_odeDxup_numRows() const { return 4; }
  integer HangGlider::Drhs_odeDxup_numCols() const { return 6; }
  integer HangGlider::Drhs_odeDxup_nnz()     const { return 14; }

  void
  HangGlider::Drhs_odeDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 0   ;
    iIndex[10] = 3   ; jIndex[10] = 2   ;
    iIndex[11] = 3   ; jIndex[11] = 3   ;
    iIndex[12] = 3   ; jIndex[12] = 4   ;
    iIndex[13] = 3   ; jIndex[13] = 5   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::Drhs_odeDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = P__[iP_T];
    result__[ 1   ] = X__[iX_vx];
    result__[ 2   ] = result__[0];
    result__[ 3   ] = X__[iX_vy];
    real_type t2   = 1.0 / ModelPars[iM_m];
    real_type t3   = t2 * result__[2];
    real_type t4   = X__[iX_x];
    real_type t5   = v(t4, result__[1], result__[3]);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t8   = ModelPars[iM_c1];
    real_type t9   = U__[iU_cL];
    real_type t10  = t9 * t9;
    real_type t13  = t10 * t8 + ModelPars[iM_c0];
    real_type t14  = Dfun(t4, result__[1], result__[3]);
    real_type t15  = t14 * t13;
    real_type t17  = Lfun(t4, result__[1], result__[3]);
    real_type t18  = t17 * t9;
    real_type t19  = w(t4, result__[3]);
    real_type t21  = -result__[1] * t15 - t19 * t18;
    real_type t22  = t21 * t7;
    real_type t23  = v_D_1(t4, result__[1], result__[3]);
    real_type t26  = 1.0 / t5;
    real_type t27  = Dfun_D_1(t4, result__[1], result__[3]);
    real_type t28  = t27 * t13;
    real_type t30  = Lfun_D_1(t4, result__[1], result__[3]);
    real_type t31  = t30 * t9;
    real_type t33  = w_D_1(t4, result__[3]);
    result__[ 4   ] = -t23 * t22 * t3 + (-t33 * t18 - t19 * t31 - result__[1] * t28) * t26 * t3;
    real_type t38  = v_D_2(t4, result__[1], result__[3]);
    real_type t41  = Dfun_D_2(t4, result__[1], result__[3]);
    real_type t42  = t41 * t13;
    real_type t44  = Lfun_D_2(t4, result__[1], result__[3]);
    real_type t45  = t44 * t9;
    result__[ 5   ] = -t38 * t22 * t3 + (-t19 * t45 - result__[1] * t42 - t15) * t26 * t3;
    real_type t50  = v_D_3(t4, result__[1], result__[3]);
    real_type t53  = Dfun_D_3(t4, result__[1], result__[3]);
    real_type t54  = t53 * t13;
    real_type t56  = Lfun_D_3(t4, result__[1], result__[3]);
    real_type t57  = t56 * t9;
    real_type t59  = w_D_2(t4, result__[3]);
    result__[ 6   ] = -t50 * t22 * t3 + (-t59 * t18 - t19 * t57 - result__[1] * t54) * t26 * t3;
    real_type t64  = t9 * t8;
    result__[ 7   ] = (-2 * result__[1] * t14 * t64 - t19 * t17) * t26 * t3;
    real_type t71  = t26 * t2;
    result__[ 8   ] = t21 * t71;
    real_type t74  = -t19 * t15 + result__[1] * t18;
    real_type t75  = t74 * t7;
    result__[ 9   ] = -t23 * t75 * t3 + (-t33 * t15 - t19 * t28 + result__[1] * t31) * t26 * t3;
    result__[ 10  ] = -t38 * t75 * t3 + (-t19 * t42 + result__[1] * t45 + t18) * t26 * t3;
    result__[ 11  ] = -t50 * t75 * t3 + (-t59 * t15 - t54 * t19 + result__[1] * t57) * t26 * t3;
    result__[ 12  ] = (-2 * t19 * t14 * t64 + result__[1] * t17) * t26 * t3;
    result__[ 13  ] = t74 * t71 - ModelPars[iM_g];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxup_sparse", 14, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::A_numRows() const { return 4; }
  integer HangGlider::A_numCols() const { return 4; }
  integer HangGlider::A_nnz()     const { return 4; }

  void
  HangGlider::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 4, i_segment );
  }

}

// EOF: HangGlider_Methods_ODE.cc
