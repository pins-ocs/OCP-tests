/*-----------------------------------------------------------------------*\
 |  file: Farmer_Methods_AdjointODE.cc                                   |
 |                                                                       |
 |  version: 1.0   date 3/6/2022                                         |
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
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Farmer::Hxp_numEqns() const { return 5; }

  void
  Farmer::Hxp_eval(
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
    result__[ 0   ] = 2 * t3 * t21 + 2 * t4 * t2 - 2 * (-t4 + U__[iU_x1__o]) * ModelPars[iM_wJ1] - L__[iL_lambda1__xo] / ModelPars[iM_tau__1];
    result__[ 1   ] = 2 * t7 * t21 + 2 * t8 * t6 - 2 * (-t8 + U__[iU_x2__o]) * ModelPars[iM_wJ2] - L__[iL_lambda2__xo] / ModelPars[iM_tau__2];
    real_type t64  = L__[iL_lambda4__xo] / ModelPars[iM_tau__4];
    result__[ 2   ] = 2 * t11 * t21 + 2 * t12 * t10 - 2 * (-t12 + U__[iU_x3__o]) * ModelPars[iM_wJ3] - L__[iL_lambda3__xo] / ModelPars[iM_tau__3] + t64;
    result__[ 3   ] = 0;
    result__[ 4   ] = 2 * t15 * t21 + 2 * t16 * t14 - 2 * (-t16 + U__[iU_x4__o]) * ModelPars[iM_wJ4] - t64 - L__[iL_lambda5__xo] / ModelPars[iM_tau__5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Farmer::DHxpDxpu_numRows() const { return 5; }
  integer Farmer::DHxpDxpu_numCols() const { return 9; }
  integer Farmer::DHxpDxpu_nnz()     const { return 20; }

  void
  Farmer::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  }


  void
  Farmer::DHxpDxpu_sparse(
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
    result__[ 4   ] = -2 * t6;
    result__[ 5   ] = result__[1];
    real_type t22  = t8 * t8;
    real_type t25  = ModelPars[iM_wJ2];
    result__[ 6   ] = 2 / t22 * t1 + 2 * t8 + 2 * t25;
    result__[ 7   ] = 2 * t9 * t15;
    result__[ 8   ] = 2 * t9 * t19;
    result__[ 9   ] = -2 * t25;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t30  = t13 * t13;
    real_type t33  = ModelPars[iM_wJ3];
    result__[ 12  ] = 2 / t30 * t1 + 2 * t13 + 2 * t33;
    result__[ 13  ] = 2 * t14 * t19;
    result__[ 14  ] = -2 * t33;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t37  = t17 * t17;
    real_type t40  = ModelPars[iM_wJ4];
    result__[ 18  ] = 2 / t37 * t1 + 2 * t17 + 2 * t40;
    result__[ 19  ] = -2 * t40;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 20, i_segment );
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

  integer Farmer::Hu_numEqns() const { return 4; }

  void
  Farmer::Hu_eval(
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
    result__[ 0   ] = 2 * ModelPars[iM_wJ1] * (-X__[iX_x1] + U__[iU_x1__o]) + L__[iL_lambda1__xo] / ModelPars[iM_tau__1];
    result__[ 1   ] = 2 * ModelPars[iM_wJ2] * (-X__[iX_x2] + U__[iU_x2__o]) + L__[iL_lambda2__xo] / ModelPars[iM_tau__2];
    result__[ 2   ] = 2 * ModelPars[iM_wJ3] * (-X__[iX_x3] + U__[iU_x3__o]) + L__[iL_lambda3__xo] / ModelPars[iM_tau__3];
    result__[ 3   ] = 2 * ModelPars[iM_wJ4] * (-X__[iX_x4] + U__[iU_x4__o]) + L__[iL_lambda5__xo] / ModelPars[iM_tau__5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 4, i_segment );
  }

}

// EOF: Farmer_Methods_AdjointODE.cc
