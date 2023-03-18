/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_AdjointODE.cc                               |
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
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::Hxp_numEqns() const { return 5; }

  void
  HangGlider::Hxp_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[2];
    real_type t2   = P__[iP_T];
    real_type t4   = 1.0 / ModelPars[iM_m];
    real_type t5   = t4 * t2;
    real_type t6   = X__[iX_x];
    real_type t7   = X__[iX_vx];
    real_type t8   = X__[iX_vy];
    real_type t9   = v(t6, t7, t8);
    real_type t10  = t9 * t9;
    real_type t11  = 1.0 / t10;
    real_type t13  = U__[iU_cL];
    real_type t14  = t13 * t13;
    real_type t17  = t14 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t18  = Dfun(t6, t7, t8);
    real_type t19  = t18 * t17;
    real_type t21  = Lfun(t6, t7, t8);
    real_type t22  = t21 * t13;
    real_type t23  = w(t6, t8);
    real_type t25  = -t7 * t19 - t23 * t22;
    real_type t26  = t25 * t11;
    real_type t27  = v_D_1(t6, t7, t8);
    real_type t30  = 1.0 / t9;
    real_type t31  = Dfun_D_1(t6, t7, t8);
    real_type t32  = t31 * t17;
    real_type t34  = Lfun_D_1(t6, t7, t8);
    real_type t35  = t34 * t13;
    real_type t37  = w_D_1(t6, t8);
    real_type t44  = MU__[3];
    real_type t47  = -t23 * t19 + t7 * t22;
    real_type t48  = t47 * t11;
    result__[ 0   ] = (-t27 * t26 * t5 + (-t37 * t22 - t23 * t35 - t7 * t32) * t30 * t5) * t1 + (-t27 * t48 * t5 + (-t37 * t19 - t23 * t32 + t7 * t35) * t30 * t5) * t44;
    result__[ 1   ] = 0;
    real_type t59  = MU__[0];
    real_type t61  = v_D_2(t6, t7, t8);
    real_type t64  = Dfun_D_2(t6, t7, t8);
    real_type t65  = t64 * t17;
    real_type t67  = Lfun_D_2(t6, t7, t8);
    real_type t68  = t67 * t13;
    result__[ 2   ] = t2 * t59 + (-t61 * t26 * t5 + (-t23 * t68 - t7 * t65 - t19) * t30 * t5) * t1 + (-t61 * t48 * t5 + (-t23 * t65 + t7 * t68 + t22) * t30 * t5) * t44;
    real_type t84  = MU__[1];
    real_type t86  = v_D_3(t6, t7, t8);
    real_type t89  = Dfun_D_3(t6, t7, t8);
    real_type t90  = t89 * t17;
    real_type t92  = Lfun_D_3(t6, t7, t8);
    real_type t93  = t92 * t13;
    real_type t95  = w_D_2(t6, t8);
    result__[ 3   ] = t2 * t84 + (-t86 * t26 * t5 + (-t95 * t22 - t23 * t93 - t7 * t90) * t30 * t5) * t1 + (-t86 * t48 * t5 + (-t95 * t19 - t23 * t90 + t7 * t93) * t30 * t5) * t44;
    real_type t112 = ALIAS_Tbound_D(-t2);
    result__[ 4   ] = -t112 + t7 * t59 + t8 * t84 + t25 * t30 * t4 * t1 + (t47 * t30 * t4 - ModelPars[iM_g]) * t44;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DHxpDxpuv_numRows() const { return 5; }
  integer HangGlider::DHxpDxpuv_numCols() const { return 10; }
  integer HangGlider::DHxpDxpuv_nnz()     const { return 20; }

  void
  HangGlider::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 5   ;
    iIndex[10] = 3   ; jIndex[10] = 0   ;
    iIndex[11] = 3   ; jIndex[11] = 2   ;
    iIndex[12] = 3   ; jIndex[12] = 3   ;
    iIndex[13] = 3   ; jIndex[13] = 4   ;
    iIndex[14] = 3   ; jIndex[14] = 5   ;
    iIndex[15] = 4   ; jIndex[15] = 0   ;
    iIndex[16] = 4   ; jIndex[16] = 2   ;
    iIndex[17] = 4   ; jIndex[17] = 3   ;
    iIndex[18] = 4   ; jIndex[18] = 4   ;
    iIndex[19] = 4   ; jIndex[19] = 5   ;
  }


  void
  HangGlider::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[2];
    real_type t2   = P__[iP_T];
    real_type t4   = 1.0 / ModelPars[iM_m];
    real_type t5   = t4 * t2;
    real_type t6   = X__[iX_x];
    real_type t7   = X__[iX_vx];
    real_type t8   = X__[iX_vy];
    real_type t9   = v(t6, t7, t8);
    real_type t10  = t9 * t9;
    real_type t12  = 1.0 / t10 / t9;
    real_type t13  = ModelPars[iM_c1];
    real_type t14  = U__[iU_cL];
    real_type t15  = t14 * t14;
    real_type t18  = t15 * t13 + ModelPars[iM_c0];
    real_type t19  = Dfun(t6, t7, t8);
    real_type t20  = t19 * t18;
    real_type t22  = Lfun(t6, t7, t8);
    real_type t23  = t22 * t14;
    real_type t24  = w(t6, t8);
    real_type t26  = -t7 * t20 - t24 * t23;
    real_type t27  = t26 * t12;
    real_type t28  = v_D_1(t6, t7, t8);
    real_type t29  = t28 * t28;
    real_type t33  = 1.0 / t10;
    real_type t34  = Dfun_D_1(t6, t7, t8);
    real_type t35  = t34 * t18;
    real_type t37  = Lfun_D_1(t6, t7, t8);
    real_type t38  = t37 * t14;
    real_type t40  = w_D_1(t6, t8);
    real_type t42  = -t40 * t23 - t24 * t38 - t7 * t35;
    real_type t43  = t42 * t33;
    real_type t47  = t26 * t33;
    real_type t48  = v_D_1_1(t6, t7, t8);
    real_type t51  = 1.0 / t9;
    real_type t52  = Dfun_D_1_1(t6, t7, t8);
    real_type t53  = t52 * t18;
    real_type t55  = Lfun_D_1_1(t6, t7, t8);
    real_type t56  = t55 * t14;
    real_type t60  = w_D_1_1(t6, t8);
    real_type t67  = MU__[3];
    real_type t70  = -t24 * t20 + t7 * t23;
    real_type t71  = t70 * t12;
    real_type t78  = -t40 * t20 - t24 * t35 + t7 * t38;
    real_type t79  = t78 * t33;
    real_type t83  = t70 * t33;
    result__[ 0   ] = (2 * t29 * t27 * t5 - 2 * t28 * t43 * t5 - t48 * t47 * t5 + (-t60 * t23 - t24 * t56 - 2 * t40 * t38 - t7 * t53) * t51 * t5) * t1 + (2 * t29 * t71 * t5 - 2 * t28 * t79 * t5 - t48 * t83 * t5 + (-t60 * t20 - t24 * t53 - 2 * t40 * t35 + t7 * t56) * t51 * t5) * t67;
    real_type t96  = t12 * t5;
    real_type t97  = t28 * t26;
    real_type t98  = v_D_2(t6, t7, t8);
    real_type t102 = Dfun_D_2(t6, t7, t8);
    real_type t103 = t102 * t18;
    real_type t105 = Lfun_D_2(t6, t7, t8);
    real_type t106 = t105 * t14;
    real_type t108 = -t7 * t103 - t24 * t106 - t20;
    real_type t109 = t108 * t33;
    real_type t112 = v_D_1_2(t6, t7, t8);
    real_type t117 = Dfun_D_1_2(t6, t7, t8);
    real_type t118 = t117 * t18;
    real_type t120 = Lfun_D_1_2(t6, t7, t8);
    real_type t121 = t120 * t14;
    real_type t129 = t28 * t70;
    real_type t135 = -t24 * t103 + t7 * t106 + t23;
    real_type t136 = t135 * t33;
    result__[ 1   ] = (2 * t98 * t97 * t96 - t28 * t109 * t5 - t112 * t47 * t5 - t98 * t43 * t5 + (-t40 * t106 - t7 * t118 - t24 * t121 - t35) * t51 * t5) * t1 + (2 * t98 * t129 * t96 - t28 * t136 * t5 - t112 * t83 * t5 - t98 * t79 * t5 + (-t40 * t103 - t24 * t118 + t7 * t121 + t38) * t51 * t5) * t67;
    real_type t151 = v_D_3(t6, t7, t8);
    real_type t155 = Dfun_D_3(t6, t7, t8);
    real_type t156 = t155 * t18;
    real_type t158 = Lfun_D_3(t6, t7, t8);
    real_type t159 = t158 * t14;
    real_type t161 = w_D_2(t6, t8);
    real_type t163 = -t7 * t156 - t24 * t159 - t161 * t23;
    real_type t164 = t163 * t33;
    real_type t167 = v_D_1_3(t6, t7, t8);
    real_type t172 = Dfun_D_1_3(t6, t7, t8);
    real_type t173 = t172 * t18;
    real_type t175 = Lfun_D_1_3(t6, t7, t8);
    real_type t176 = t175 * t14;
    real_type t180 = w_D_1_2(t6, t8);
    real_type t193 = -t24 * t156 + t7 * t159 - t161 * t20;
    real_type t194 = t193 * t33;
    result__[ 2   ] = (2 * t151 * t97 * t96 - t28 * t164 * t5 - t167 * t47 * t5 - t151 * t43 * t5 + (-t40 * t159 - t161 * t38 - t7 * t173 - t24 * t176 - t180 * t23) * t51 * t5) * t1 + (2 * t151 * t129 * t96 - t28 * t194 * t5 - t167 * t83 * t5 - t151 * t79 * t5 + (-t40 * t156 - t161 * t35 - t24 * t173 + t7 * t176 - t180 * t20) * t51 * t5) * t67;
    real_type t211 = t33 * t4;
    real_type t213 = t51 * t4;
    real_type t220 = (-t129 * t211 + t78 * t213) * t67;
    result__[ 3   ] = (-t97 * t211 + t42 * t213) * t1 + t220;
    real_type t221 = t14 * t13;
    real_type t226 = -2 * t7 * t19 * t221 - t24 * t22;
    real_type t227 = t226 * t33;
    real_type t244 = -2 * t24 * t19 * t221 + t7 * t22;
    real_type t245 = t244 * t33;
    result__[ 4   ] = (-t28 * t227 * t5 + (-2 * t7 * t34 * t221 - t40 * t22 - t24 * t37) * t51 * t5) * t1 + (-t28 * t245 * t5 + (-2 * t40 * t19 * t221 - 2 * t24 * t34 * t221 + t7 * t37) * t51 * t5) * t67;
    result__[ 5   ] = result__[1];
    real_type t260 = t98 * t98;
    real_type t267 = v_D_2_2(t6, t7, t8);
    real_type t270 = Dfun_D_2_2(t6, t7, t8);
    real_type t271 = t270 * t18;
    real_type t274 = Lfun_D_2_2(t6, t7, t8);
    real_type t275 = t274 * t14;
    result__[ 6   ] = (2 * t260 * t27 * t5 - 2 * t98 * t109 * t5 - t267 * t47 * t5 + (-t24 * t275 - t7 * t271 - 2 * t103) * t51 * t5) * t1 + (2 * t260 * t71 * t5 - 2 * t98 * t136 * t5 - t267 * t83 * t5 + (-t24 * t271 + t7 * t275 + 2 * t106) * t51 * t5) * t67;
    real_type t298 = t98 * t26;
    real_type t304 = v_D_2_3(t6, t7, t8);
    real_type t309 = Dfun_D_2_3(t6, t7, t8);
    real_type t310 = t309 * t18;
    real_type t312 = Lfun_D_2_3(t6, t7, t8);
    real_type t313 = t312 * t14;
    real_type t321 = t98 * t70;
    result__[ 7   ] = (2 * t151 * t298 * t96 - t98 * t164 * t5 - t304 * t47 * t5 - t151 * t109 * t5 + (-t161 * t106 - t24 * t313 - t7 * t310 - t156) * t51 * t5) * t1 + (2 * t151 * t321 * t96 - t98 * t194 * t5 - t304 * t83 * t5 - t151 * t136 * t5 + (-t161 * t103 - t24 * t310 + t7 * t313 + t159) * t51 * t5) * t67;
    real_type t339 = MU__[0];
    real_type t347 = (t135 * t213 - t321 * t211) * t67;
    result__[ 8   ] = t339 + (t108 * t213 - t298 * t211) * t1 + t347;
    result__[ 9   ] = (-t98 * t227 * t5 + (-2 * t7 * t102 * t221 - t24 * t105 - 2 * t19 * t221) * t51 * t5) * t1 + (-t98 * t245 * t5 + (-2 * t24 * t102 * t221 + t7 * t105 + t22) * t51 * t5) * t67;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t372 = t151 * t151;
    real_type t379 = v_D_3_3(t6, t7, t8);
    real_type t382 = Dfun_D_3_3(t6, t7, t8);
    real_type t383 = t382 * t18;
    real_type t385 = Lfun_D_3_3(t6, t7, t8);
    real_type t386 = t385 * t14;
    real_type t390 = w_D_2_2(t6, t8);
    result__[ 12  ] = (2 * t372 * t27 * t5 - 2 * t151 * t164 * t5 - t379 * t47 * t5 + (-2 * t161 * t159 - t390 * t23 - t24 * t386 - t7 * t383) * t51 * t5) * t1 + (2 * t372 * t71 * t5 - 2 * t151 * t194 * t5 - t379 * t83 * t5 + (-2 * t161 * t156 - t390 * t20 - t24 * t383 + t7 * t386) * t51 * t5) * t67;
    real_type t415 = MU__[1];
    real_type t425 = (-t151 * t70 * t211 + t193 * t213) * t67;
    result__[ 13  ] = t415 + (-t151 * t26 * t211 + t163 * t213) * t1 + t425;
    result__[ 14  ] = (-t151 * t227 * t5 + (-2 * t7 * t155 * t221 - t24 * t158 - t161 * t22) * t51 * t5) * t1 + (-t151 * t245 * t5 + (-2 * t24 * t155 * t221 - 2 * t161 * t19 * t221 + t7 * t158) * t51 * t5) * t67;
    real_type t452 = t4 * t1;
    result__[ 15  ] = -t28 * t47 * t452 + t42 * t51 * t452 + t220;
    result__[ 16  ] = t108 * t51 * t452 - t98 * t47 * t452 + t339 + t347;
    result__[ 17  ] = -t151 * t47 * t452 + t163 * t51 * t452 + t415 + t425;
    result__[ 18  ] = ALIAS_Tbound_DD(-t2);
    result__[ 19  ] = t244 * t51 * t4 * t67 + t226 * t51 * t452;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 20, i_segment );
  }

}

// EOF: HangGlider_Methods_AdjointODE.cc
