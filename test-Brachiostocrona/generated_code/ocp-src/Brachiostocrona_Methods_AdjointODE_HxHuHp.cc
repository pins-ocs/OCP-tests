/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona_Methods_AdjointODE.cc                          |
 |                                                                       |
 |  version: 1.0   date 17/6/2022                                        |
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


#include "Brachiostocrona.hh"
#include "Brachiostocrona_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::PenaltyBarrier1DGreaterThan;
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
#define ALIAS_penalization_DD(__t1) Pen1D.evaluate_DD( __t1)
#define ALIAS_penalization_D(__t1) Pen1D.evaluate_D( __t1)
#define ALIAS_penalization(__t1) Pen1D.evaluate( __t1)
#define ALIAS_vthetaControl_D_3(__t1, __t2, __t3) vthetaControl.D_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2(__t1, __t2, __t3) vthetaControl.D_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1(__t1, __t2, __t3) vthetaControl.D_1( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_3_3(__t1, __t2, __t3) vthetaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_3(__t1, __t2, __t3) vthetaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_2(__t1, __t2, __t3) vthetaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_3(__t1, __t2, __t3) vthetaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_2(__t1, __t2, __t3) vthetaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_1(__t1, __t2, __t3) vthetaControl.D_1_1( __t1, __t2, __t3)


namespace BrachiostocronaDefine {

  /*\
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona::Hxp_numEqns() const { return 5; }

  void
  Brachiostocrona::Hxp_eval(
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
    real_type t2   = ModelPars[iM_slope_low];
    real_type t9   = (t2 * X__[iX_x] + U__[iU_sz] - X__[iX_y] + ModelPars[iM_y0_low]) * ModelPars[iM_w_ARG];
    result__[ 0   ] = 2 * t2 * t9;
    result__[ 1   ] = -2 * t9;
    real_type t12  = L__[iL_lambda1__xo];
    real_type t13  = P__[iP_T];
    real_type t14  = t13 * t12;
    real_type t15  = X__[iX_theta];
    real_type t16  = cos(t15);
    real_type t18  = L__[iL_lambda2__xo];
    real_type t19  = t13 * t18;
    real_type t20  = sin(t15);
    result__[ 2   ] = t16 * t14 + t20 * t19;
    real_type t22  = X__[iX_v];
    real_type t27  = L__[iL_lambda3__xo];
    real_type t29  = ModelPars[iM_g];
    result__[ 3   ] = -t16 * t29 * t13 * t27 - t20 * t22 * t14 + t16 * t22 * t19;
    result__[ 4   ] = t16 * t22 * t12 + t20 * t22 * t18 - t20 * t29 * t27;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::DHxpDxpu_numRows() const { return 5; }
  integer Brachiostocrona::DHxpDxpu_numCols() const { return 7; }
  integer Brachiostocrona::DHxpDxpu_nnz()     const { return 13; }

  void
  Brachiostocrona::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 3   ;
    iIndex[10] = 3   ; jIndex[10] = 4   ;
    iIndex[11] = 4   ; jIndex[11] = 2   ;
    iIndex[12] = 4   ; jIndex[12] = 3   ;
  }


  void
  Brachiostocrona::DHxpDxpu_sparse(
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
    real_type t1   = ModelPars[iM_w_ARG];
    real_type t2   = ModelPars[iM_slope_low];
    real_type t3   = t2 * t2;
    result__[ 0   ] = 2 * t3 * t1;
    real_type t6   = 2 * t2 * t1;
    result__[ 1   ] = -t6;
    result__[ 2   ] = t6;
    result__[ 3   ] = result__[1];
    result__[ 4   ] = 2 * t1;
    result__[ 5   ] = -result__[4];
    real_type t7   = L__[iL_lambda1__xo];
    real_type t8   = P__[iP_T];
    real_type t9   = t8 * t7;
    real_type t10  = X__[iX_theta];
    real_type t11  = sin(t10);
    real_type t13  = L__[iL_lambda2__xo];
    real_type t14  = t8 * t13;
    real_type t15  = cos(t10);
    result__[ 6   ] = -t11 * t9 + t15 * t14;
    result__[ 7   ] = t11 * t13 + t15 * t7;
    result__[ 8   ] = result__[6];
    real_type t19  = X__[iX_v];
    real_type t24  = L__[iL_lambda3__xo];
    real_type t26  = ModelPars[iM_g];
    result__[ 9   ] = t11 * t26 * t8 * t24 - t11 * t19 * t14 - t15 * t19 * t9;
    result__[ 10  ] = -t11 * t19 * t7 + t15 * t19 * t13 - t15 * t26 * t24;
    result__[ 11  ] = result__[7];
    result__[ 12  ] = result__[10];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 13, i_segment );
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

  integer Brachiostocrona::Hu_numEqns() const { return 2; }

  void
  Brachiostocrona::Hu_eval(
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
    result__[ 0   ] = L__[iL_lambda4__xo];
    real_type t5   = U__[iU_sz];
    real_type t11  = ALIAS_penalization_D(t5);
    result__[ 1   ] = 2 * (ModelPars[iM_slope_low] * X__[iX_x] + t5 - X__[iX_y] + ModelPars[iM_y0_low]) * ModelPars[iM_w_ARG] + t11;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

}

// EOF: Brachiostocrona_Methods_AdjointODE.cc
