/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Methods_AdjointODE.cc                    |
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


#include "LUUS_DrugDisplacement.hh"
#include "LUUS_DrugDisplacement_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace LUUS_DrugDisplacementDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::Hxp_numEqns() const { return 3; }

  void
  LUUS_DrugDisplacement::Hxp_eval(
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
    real_type t1   = MU__[0];
    real_type t2   = P__[iP_T];
    real_type t3   = X__[iX_x1];
    real_type t4   = X__[iX_x2];
    real_type t5   = g1_D_1(t3, t4);
    real_type t6   = t5 * t2;
    real_type t7   = g4(t3, t4);
    real_type t8   = 0.2e-1 - t3;
    real_type t10  = U__[iU_u];
    real_type t12  = t10 - 2 * t4;
    real_type t15  = t8 * t7 + 0.464e2 * t12 * t3;
    real_type t17  = g1(t3, t4);
    real_type t18  = t17 * t2;
    real_type t19  = g4_D_1(t3, t4);
    real_type t27  = MU__[1];
    real_type t28  = g3(t3, t4);
    real_type t31  = t12 * t28 + 0.928e0 - 0.464e2 * t3;
    real_type t33  = g3_D_1(t3, t4);
    result__[ 0   ] = (t15 * t6 + (t8 * t19 - t7 + 0.464e2 * t10 - 0.928e2 * t4) * t18) * t1 + (t31 * t6 + (t12 * t33 - 0.464e2) * t18) * t27;
    real_type t39  = g1_D_2(t3, t4);
    real_type t40  = t39 * t2;
    real_type t42  = g4_D_2(t3, t4);
    real_type t50  = g3_D_2(t3, t4);
    result__[ 1   ] = (t15 * t40 + (t8 * t42 - 0.928e2 * t3) * t18) * t1 + (t31 * t40 + (t12 * t50 - 2 * t28) * t18) * t27;
    real_type t57  = uControl(t10, 0, 8);
    result__[ 2   ] = t15 * t17 * t1 + t31 * t17 * t27 + t57;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DHxpDxpuv_numRows() const { return 3; }
  integer LUUS_DrugDisplacement::DHxpDxpuv_numCols() const { return 6; }
  integer LUUS_DrugDisplacement::DHxpDxpuv_nnz()     const { return 11; }

  void
  LUUS_DrugDisplacement::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 3   ;
  }


  void
  LUUS_DrugDisplacement::DHxpDxpuv_sparse(
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
    real_type t1   = MU__[0];
    real_type t2   = P__[iP_T];
    real_type t3   = X__[iX_x1];
    real_type t4   = X__[iX_x2];
    real_type t5   = g1_D_1_1(t3, t4);
    real_type t6   = t5 * t2;
    real_type t7   = g4(t3, t4);
    real_type t8   = 0.2e-1 - t3;
    real_type t10  = U__[iU_u];
    real_type t12  = t10 - 2 * t4;
    real_type t15  = t8 * t7 + 0.464e2 * t12 * t3;
    real_type t17  = g1_D_1(t3, t4);
    real_type t18  = t17 * t2;
    real_type t19  = g4_D_1(t3, t4);
    real_type t23  = t8 * t19 - t7 + 0.464e2 * t10 - 0.928e2 * t4;
    real_type t26  = g1(t3, t4);
    real_type t27  = t26 * t2;
    real_type t28  = g4_D_1_1(t3, t4);
    real_type t35  = MU__[1];
    real_type t36  = g3(t3, t4);
    real_type t39  = t12 * t36 + 0.928e0 - 0.464e2 * t3;
    real_type t41  = g3_D_1(t3, t4);
    real_type t43  = t12 * t41 - 0.464e2;
    real_type t46  = g3_D_1_1(t3, t4);
    result__[ 0   ] = (t15 * t6 + 2 * t23 * t18 + (t8 * t28 - 2 * t19) * t27) * t1 + (t12 * t46 * t27 + 2 * t43 * t18 + t39 * t6) * t35;
    real_type t51  = g1_D_1_2(t3, t4);
    real_type t52  = t51 * t2;
    real_type t54  = g4_D_2(t3, t4);
    real_type t57  = t8 * t54 - 0.928e2 * t3;
    real_type t59  = g1_D_2(t3, t4);
    real_type t60  = t59 * t2;
    real_type t62  = g4_D_1_2(t3, t4);
    real_type t69  = g3_D_2(t3, t4);
    real_type t72  = t12 * t69 - 2 * t36;
    real_type t75  = g3_D_1_2(t3, t4);
    result__[ 1   ] = (t15 * t52 + t57 * t18 + t23 * t60 + (t8 * t62 - t54 - 0.928e2) * t27) * t1 + (t39 * t52 + t72 * t18 + t43 * t60 + (t12 * t75 - 2 * t41) * t27) * t35;
    result__[ 2   ] = (t15 * t17 + t23 * t26) * t1 + (t39 * t17 + t43 * t26) * t35;
    result__[ 3   ] = (0.464e2 * t3 * t18 + 0.464e2 * t27) * t1 + (t36 * t18 + t41 * t27) * t35;
    result__[ 4   ] = result__[1];
    real_type t99  = g1_D_2_2(t3, t4);
    real_type t100 = t99 * t2;
    real_type t104 = g4_D_2_2(t3, t4);
    real_type t112 = g3_D_2_2(t3, t4);
    result__[ 5   ] = (t8 * t104 * t27 + t15 * t100 + 2 * t57 * t60) * t1 + (t39 * t100 + 2 * t72 * t60 + (t12 * t112 - 4 * t69) * t27) * t35;
    result__[ 6   ] = (t15 * t59 + t57 * t26) * t1 + (t72 * t26 + t39 * t59) * t35;
    result__[ 7   ] = 0.464e2 * t3 * t59 * t2 * t1 + (t69 * t27 + t36 * t60) * t35;
    real_type t137 = t26 * t1;
    real_type t141 = t26 * t35;
    result__[ 8   ] = t15 * t17 * t1 + t39 * t17 * t35 + t23 * t137 + t43 * t141;
    result__[ 9   ] = t15 * t59 * t1 + t39 * t59 * t35 + t57 * t137 + t72 * t141;
    real_type t149 = ALIAS_uControl_D_1(t10, 0, 8);
    result__[ 10  ] = t149 + 0.464e2 * t3 * t137 + t36 * t141;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 11, i_segment );
  }

}

// EOF: LUUS_DrugDisplacement_Methods_AdjointODE.cc
