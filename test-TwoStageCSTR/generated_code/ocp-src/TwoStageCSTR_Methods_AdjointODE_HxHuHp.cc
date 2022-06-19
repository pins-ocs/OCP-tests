/*-----------------------------------------------------------------------*\
 |  file: TwoStageCSTR_Methods_AdjointODE.cc                             |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


#include "TwoStageCSTR.hh"
#include "TwoStageCSTR_Pars.hh"

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
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace TwoStageCSTRDefine {

  /*\
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoStageCSTR::Hxp_numEqns() const { return 4; }

  void
  TwoStageCSTR::Hxp_eval(
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
    real_type t1   = X__[iX_x1];
    real_type t3   = L__[iL_lambda1__xo];
    real_type t4   = X__[iX_x2];
    real_type t5   = R1_D_1(t1, t4);
    real_type t6   = -1 - t5;
    real_type t8   = L__[iL_lambda2__xo];
    real_type t10  = L__[iL_lambda3__xo];
    real_type t11  = ModelPars[iM_tau];
    real_type t15  = L__[iL_lambda4__xo];
    result__[ 0   ] = 2 * t1 + t6 * t3 + t5 * t8 + (-t6 * t11 + 1) * t10 - t5 * t11 * t15;
    real_type t19  = R1_D_2(t1, t4);
    real_type t22  = t19 - 2 - U__[iU_u1];
    result__[ 1   ] = 2 * t4 - t19 * t3 + t22 * t8 + t19 * t11 * t10 + (-t22 * t11 + 1) * t15;
    real_type t29  = X__[iX_x3];
    real_type t31  = X__[iX_x4];
    real_type t32  = R2_D_1(t29, t31);
    result__[ 2   ] = 2 * t29 + (-1 - t32) * t10 + t32 * t15;
    real_type t37  = R2_D_2(t29, t31);
    result__[ 3   ] = 2 * t31 - t37 * t10 + (-2 - U__[iU_u2] + t37) * t15;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoStageCSTR::DHxpDxpu_numRows() const { return 4; }
  integer TwoStageCSTR::DHxpDxpu_numCols() const { return 6; }
  integer TwoStageCSTR::DHxpDxpu_nnz()     const { return 10; }

  void
  TwoStageCSTR::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 5   ;
  }


  void
  TwoStageCSTR::DHxpDxpu_sparse(
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
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = R1_D_1_1(t2, t3);
    real_type t6   = L__[iL_lambda2__xo];
    real_type t8   = L__[iL_lambda3__xo];
    real_type t9   = ModelPars[iM_tau];
    real_type t10  = t9 * t8;
    real_type t12  = L__[iL_lambda4__xo];
    real_type t13  = t9 * t12;
    result__[ 0   ] = -t4 * t1 + t4 * t10 - t4 * t13 + t4 * t6 + 2;
    real_type t15  = R1_D_1_2(t2, t3);
    result__[ 1   ] = -t15 * t1 + t15 * t10 - t15 * t13 + t15 * t6;
    result__[ 2   ] = result__[1];
    real_type t20  = R1_D_2_2(t2, t3);
    result__[ 3   ] = -t20 * t1 + t20 * t10 - t20 * t13 + t20 * t6 + 2;
    result__[ 4   ] = t13 - t6;
    real_type t25  = X__[iX_x3];
    real_type t26  = X__[iX_x4];
    real_type t27  = R2_D_1_1(t25, t26);
    result__[ 5   ] = t27 * t12 - t27 * t8 + 2;
    real_type t30  = R2_D_1_2(t25, t26);
    result__[ 6   ] = t30 * t12 - t30 * t8;
    result__[ 7   ] = result__[6];
    real_type t33  = R2_D_2_2(t25, t26);
    result__[ 8   ] = t33 * t12 - t33 * t8 + 2;
    result__[ 9   ] = -t12;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 10, i_segment );
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

  integer TwoStageCSTR::Hu_numEqns() const { return 2; }

  void
  TwoStageCSTR::Hu_eval(
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
    real_type t1   = ModelPars[iM_W];
    real_type t7   = -X__[iX_x2] - 0.25e0;
    real_type t9   = L__[iL_lambda4__xo];
    result__[ 0   ] = -t7 * ModelPars[iM_tau] * t9 + 2 * U__[iU_u1] * t1 + t7 * L__[iL_lambda2__xo];
    result__[ 1   ] = 2 * U__[iU_u2] * t1 + (-X__[iX_x4] - 0.25e0) * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

}

// EOF: TwoStageCSTR_Methods_AdjointODE.cc
