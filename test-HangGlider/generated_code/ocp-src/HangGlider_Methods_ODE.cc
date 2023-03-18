/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_ODE.cc                                      |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
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
#pragma warning( disable : 4189 )
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

  integer HangGlider::ode_numEqns() const { return 4; }

  void
  HangGlider::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_vx];
    result__[ 0   ] = t2 * t1 - V__[0];
    real_type t5   = X__[iX_vy];
    result__[ 1   ] = t5 * t1 - V__[1];
    real_type t10  = 1.0 / ModelPars[iM_m] * t1;
    real_type t11  = X__[iX_x];
    real_type t12  = v(t11, t2, t5);
    real_type t13  = 1.0 / t12;
    real_type t15  = U__[iU_cL];
    real_type t16  = t15 * t15;
    real_type t20  = Dfun(t11, t2, t5);
    real_type t21  = t20 * (t16 * ModelPars[iM_c1] + ModelPars[iM_c0]);
    real_type t23  = Lfun(t11, t2, t5);
    real_type t24  = t23 * t15;
    real_type t25  = w(t11, t5);
    result__[ 2   ] = (-t2 * t21 - t25 * t24) * t13 * t10 - V__[2];
    result__[ 3   ] = (t2 * t24 - t25 * t21) * t13 * t10 - ModelPars[iM_g] * t1 - V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DodeDxpuv_numRows() const { return 4; }
  integer HangGlider::DodeDxpuv_numCols() const { return 10; }
  integer HangGlider::DodeDxpuv_nnz()     const { return 18; }

  void
  HangGlider::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 4   ;
    iIndex[10] = 2   ; jIndex[10] = 5   ;
    iIndex[11] = 2   ; jIndex[11] = 8   ;
    iIndex[12] = 3   ; jIndex[12] = 0   ;
    iIndex[13] = 3   ; jIndex[13] = 2   ;
    iIndex[14] = 3   ; jIndex[14] = 3   ;
    iIndex[15] = 3   ; jIndex[15] = 4   ;
    iIndex[16] = 3   ; jIndex[16] = 5   ;
    iIndex[17] = 3   ; jIndex[17] = 9   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = P__[iP_T];
    result__[ 1   ] = X__[iX_vx];
    result__[ 2   ] = -1;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = X__[iX_vy];
    result__[ 5   ] = -1;
    real_type t2   = 1.0 / ModelPars[iM_m];
    real_type t3   = t2 * result__[3];
    real_type t4   = X__[iX_x];
    real_type t5   = v(t4, result__[1], result__[4]);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t8   = ModelPars[iM_c1];
    real_type t9   = U__[iU_cL];
    real_type t10  = t9 * t9;
    real_type t13  = t10 * t8 + ModelPars[iM_c0];
    real_type t14  = Dfun(t4, result__[1], result__[4]);
    real_type t15  = t14 * t13;
    real_type t17  = Lfun(t4, result__[1], result__[4]);
    real_type t18  = t17 * t9;
    real_type t19  = w(t4, result__[4]);
    real_type t21  = -t15 * result__[1] - t18 * t19;
    real_type t22  = t21 * t7;
    real_type t23  = v_D_1(t4, result__[1], result__[4]);
    real_type t26  = 1.0 / t5;
    real_type t27  = Dfun_D_1(t4, result__[1], result__[4]);
    real_type t28  = t27 * t13;
    real_type t30  = Lfun_D_1(t4, result__[1], result__[4]);
    real_type t31  = t30 * t9;
    real_type t33  = w_D_1(t4, result__[4]);
    result__[ 6   ] = -t23 * t22 * t3 + (-t18 * t33 - t19 * t31 - t28 * result__[1]) * t26 * t3;
    real_type t38  = v_D_2(t4, result__[1], result__[4]);
    real_type t41  = Dfun_D_2(t4, result__[1], result__[4]);
    real_type t42  = t41 * t13;
    real_type t44  = Lfun_D_2(t4, result__[1], result__[4]);
    real_type t45  = t44 * t9;
    result__[ 7   ] = -t38 * t22 * t3 + (-t19 * t45 - t42 * result__[1] - t15) * t26 * t3;
    real_type t50  = v_D_3(t4, result__[1], result__[4]);
    real_type t53  = Dfun_D_3(t4, result__[1], result__[4]);
    real_type t54  = t53 * t13;
    real_type t56  = Lfun_D_3(t4, result__[1], result__[4]);
    real_type t57  = t56 * t9;
    real_type t59  = w_D_2(t4, result__[4]);
    result__[ 8   ] = -t50 * t22 * t3 + (-t18 * t59 - t19 * t57 - t54 * result__[1]) * t26 * t3;
    real_type t64  = t26 * t2;
    result__[ 9   ] = t21 * t64;
    real_type t65  = t9 * t8;
    result__[ 10  ] = (-2 * t14 * t65 * result__[1] - t17 * t19) * t26 * t3;
    result__[ 11  ] = -1;
    real_type t74  = -t15 * t19 + t18 * result__[1];
    real_type t75  = t74 * t7;
    result__[ 12  ] = -t23 * t75 * t3 + (-t15 * t33 - t19 * t28 + t31 * result__[1]) * t26 * t3;
    result__[ 13  ] = -t38 * t75 * t3 + (-t19 * t42 + t45 * result__[1] + t18) * t26 * t3;
    result__[ 14  ] = -t50 * t75 * t3 + (-t15 * t59 - t19 * t54 + result__[1] * t57) * t26 * t3;
    result__[ 15  ] = t64 * t74 - ModelPars[iM_g];
    result__[ 16  ] = (-2 * t14 * t19 * t65 + t17 * result__[1]) * t26 * t3;
    result__[ 17  ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 18, i_segment );
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
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 4, i_segment );
  }

}

// EOF: HangGlider_Methods_ODE.cc
