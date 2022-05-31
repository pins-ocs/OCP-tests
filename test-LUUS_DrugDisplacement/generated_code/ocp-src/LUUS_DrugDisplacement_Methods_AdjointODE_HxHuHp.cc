/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Methods_AdjointODE.cc                    |
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
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::Hxp_numEqns() const { return 3; }

  void
  LUUS_DrugDisplacement::Hxp_eval(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1_D_1(t4, t5);
    real_type t7   = g4(t4, t5);
    real_type t8   = 0.2e-1 - t4;
    real_type t10  = U__[iU_u];
    real_type t12  = t10 - 2 * t5;
    real_type t15  = t8 * t7 + 0.464e2 * t12 * t4;
    real_type t18  = g1(t4, t5);
    real_type t19  = g4_D_1(t4, t5);
    real_type t26  = L__[iL_lambda2__xo];
    real_type t27  = t2 * t26;
    real_type t28  = g3(t4, t5);
    real_type t31  = t12 * t28 + 0.928e0 - 0.464e2 * t4;
    real_type t34  = g3_D_1(t4, t5);
    result__[ 0   ] = t15 * t6 * t3 + (t8 * t19 - t7 + 0.464e2 * t10 - 0.928e2 * t5) * t18 * t3 + t31 * t6 * t27 + (t12 * t34 - 0.464e2) * t18 * t27;
    real_type t39  = g1_D_2(t4, t5);
    real_type t42  = g4_D_2(t4, t5);
    real_type t50  = g3_D_2(t4, t5);
    result__[ 1   ] = t15 * t39 * t3 + (t8 * t42 - 0.928e2 * t4) * t18 * t3 + t31 * t39 * t27 + (t12 * t50 - 2 * t28) * t18 * t27;
    result__[ 2   ] = t15 * t18 * t1 + t31 * t18 * t26;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DHxpDxpu_numRows() const { return 3; }
  integer LUUS_DrugDisplacement::DHxpDxpu_numCols() const { return 4; }
  integer LUUS_DrugDisplacement::DHxpDxpu_nnz()     const { return 11; }

  void
  LUUS_DrugDisplacement::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  LUUS_DrugDisplacement::DHxpDxpu_sparse(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1_D_1_1(t4, t5);
    real_type t7   = g4(t4, t5);
    real_type t8   = 0.2e-1 - t4;
    real_type t10  = U__[iU_u];
    real_type t12  = t10 - 2 * t5;
    real_type t15  = t8 * t7 + 0.464e2 * t12 * t4;
    real_type t18  = g1_D_1(t4, t5);
    real_type t19  = g4_D_1(t4, t5);
    real_type t23  = t8 * t19 - t7 + 0.464e2 * t10 - 0.928e2 * t5;
    real_type t27  = g1(t4, t5);
    real_type t28  = g4_D_1_1(t4, t5);
    real_type t34  = L__[iL_lambda2__xo];
    real_type t35  = t2 * t34;
    real_type t36  = g3(t4, t5);
    real_type t39  = t12 * t36 + 0.928e0 - 0.464e2 * t4;
    real_type t42  = g3_D_1(t4, t5);
    real_type t44  = t12 * t42 - 0.464e2;
    real_type t48  = g3_D_1_1(t4, t5);
    result__[ 0   ] = t15 * t6 * t3 + 2 * t23 * t18 * t3 + (t28 * t8 - 2 * t19) * t27 * t3 + t39 * t6 * t35 + 2 * t44 * t18 * t35 + t12 * t48 * t27 * t35;
    real_type t52  = g1_D_1_2(t4, t5);
    real_type t55  = g4_D_2(t4, t5);
    real_type t58  = t8 * t55 - 0.928e2 * t4;
    real_type t61  = g1_D_2(t4, t5);
    real_type t64  = g4_D_1_2(t4, t5);
    real_type t71  = g3_D_2(t4, t5);
    real_type t74  = t12 * t71 - 2 * t36;
    real_type t79  = g3_D_1_2(t4, t5);
    result__[ 1   ] = t15 * t52 * t3 + t58 * t18 * t3 + t23 * t61 * t3 + (t8 * t64 - t55 - 0.928e2) * t27 * t3 + t39 * t52 * t35 + t74 * t18 * t35 + t44 * t61 * t35 + (t12 * t79 - 2 * t42) * t27 * t35;
    real_type t87  = t27 * t1;
    real_type t91  = t27 * t34;
    result__[ 2   ] = t1 * t15 * t18 + t18 * t34 * t39 + t23 * t87 + t44 * t91;
    result__[ 3   ] = 0.464e2 * t4 * t18 * t3 + 0.464e2 * t27 * t3 + t36 * t18 * t35 + t42 * t27 * t35;
    result__[ 4   ] = result__[1];
    real_type t102 = g1_D_2_2(t4, t5);
    real_type t108 = g4_D_2_2(t4, t5);
    real_type t117 = g3_D_2_2(t4, t5);
    result__[ 5   ] = t15 * t102 * t3 + 2 * t58 * t61 * t3 + t8 * t108 * t27 * t3 + t39 * t102 * t35 + 2 * t74 * t61 * t35 + (t117 * t12 - 4 * t71) * t27 * t35;
    result__[ 6   ] = t1 * t15 * t61 + t34 * t39 * t61 + t58 * t87 + t74 * t91;
    result__[ 7   ] = 0.464e2 * t4 * t61 * t3 + t36 * t61 * t35 + t71 * t27 * t35;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    result__[ 10  ] = 0.464e2 * t4 * t87 + t36 * t91;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 11, i_segment );
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::Hu_numEqns() const { return 1; }

  void
  LUUS_DrugDisplacement::Hu_eval(
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
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1(t4, t5);
    real_type t12  = g3(t4, t5);
    result__[ 0   ] = 0.464e2 * t4 * t6 * t2 * L__[iL_lambda1__xo] + t12 * t6 * t2 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

}

// EOF: LUUS_DrugDisplacement_Methods_AdjointODE.cc
