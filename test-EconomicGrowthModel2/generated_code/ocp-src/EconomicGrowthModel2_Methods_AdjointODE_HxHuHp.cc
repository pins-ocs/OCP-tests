/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods_AdjointODE.cc                     |
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


#include "EconomicGrowthModel2.hh"
#include "EconomicGrowthModel2_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace EconomicGrowthModel2Define {

  /*\
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel2::Hxp_numEqns() const { return 5; }

  void
  EconomicGrowthModel2::Hxp_eval(
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
    real_type t2   = U__[iU_u];
    real_type t3   = t2 * L__[iL_lambda2__xo];
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = Q_D_1(t4, t5);
    real_type t7   = X__[iX_T];
    real_type t8   = t7 * t6;
    real_type t12  = (1 - t2) * L__[iL_lambda4__xo];
    result__[ 0   ] = t8 * t12 + t8 * t3;
    real_type t14  = Q_D_2(t4, t5);
    real_type t15  = t7 * t14;
    result__[ 1   ] = t15 * t12 + t15 * t3;
    real_type t18  = L__[iL_lambda1__xo];
    result__[ 2   ] = t7 * t18;
    real_type t19  = L__[iL_lambda3__xo];
    result__[ 3   ] = t7 * t19;
    real_type t22  = Q(t4, t5);
    result__[ 4   ] = t22 * t12 + X__[iX_y1] * t18 + X__[iX_y2] * t19 + t22 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DHxpDxpu_numRows() const { return 5; }
  integer EconomicGrowthModel2::DHxpDxpu_numCols() const { return 6; }
  integer EconomicGrowthModel2::DHxpDxpu_nnz()     const { return 15; }

  void
  EconomicGrowthModel2::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 4   ;
    iIndex[10] = 4   ; jIndex[10] = 0   ;
    iIndex[11] = 4   ; jIndex[11] = 1   ;
    iIndex[12] = 4   ; jIndex[12] = 2   ;
    iIndex[13] = 4   ; jIndex[13] = 3   ;
    iIndex[14] = 4   ; jIndex[14] = 5   ;
  }


  void
  EconomicGrowthModel2::DHxpDxpu_sparse(
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
    real_type t1   = L__[iL_lambda2__xo];
    real_type t2   = U__[iU_u];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = Q_D_1_1(t4, t5);
    real_type t7   = X__[iX_T];
    real_type t8   = t7 * t6;
    real_type t10  = L__[iL_lambda4__xo];
    real_type t12  = (1 - t2) * t10;
    result__[ 0   ] = t12 * t8 + t3 * t8;
    real_type t14  = Q_D_1_2(t4, t5);
    real_type t15  = t7 * t14;
    result__[ 1   ] = t12 * t15 + t15 * t3;
    real_type t18  = Q_D_1(t4, t5);
    result__[ 2   ] = t12 * t18 + t18 * t3;
    result__[ 3   ] = t1 * t18 * t7 - t10 * t18 * t7;
    result__[ 4   ] = result__[1];
    real_type t25  = Q_D_2_2(t4, t5);
    real_type t26  = t7 * t25;
    result__[ 5   ] = t12 * t26 + t26 * t3;
    real_type t29  = Q_D_2(t4, t5);
    result__[ 6   ] = t12 * t29 + t29 * t3;
    result__[ 7   ] = t1 * t29 * t7 - t10 * t29 * t7;
    result__[ 8   ] = L__[iL_lambda1__xo];
    result__[ 9   ] = L__[iL_lambda3__xo];
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[6];
    result__[ 12  ] = result__[8];
    result__[ 13  ] = result__[9];
    real_type t36  = Q(t4, t5);
    result__[ 14  ] = t1 * t36 - t10 * t36;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 15, i_segment );
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

  integer EconomicGrowthModel2::Hu_numEqns() const { return 1; }

  void
  EconomicGrowthModel2::Hu_eval(
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
    real_type t4   = Q(X__[iX_x1], X__[iX_x2]);
    real_type t6   = X__[iX_T];
    result__[ 0   ] = t6 * t4 * L__[iL_lambda2__xo] - t6 * t4 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

}

// EOF: EconomicGrowthModel2_Methods_AdjointODE.cc
