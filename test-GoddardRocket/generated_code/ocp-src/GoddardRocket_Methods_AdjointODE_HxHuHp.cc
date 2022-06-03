/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods_AdjointODE.cc                            |
 |                                                                       |
 |  version: 1.0   date 14/6/2022                                        |
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


#include "GoddardRocket.hh"
#include "GoddardRocket_Pars.hh"

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
#define ALIAS_TSPositive_DD(__t1) TSPositive.DD( __t1)
#define ALIAS_TSPositive_D(__t1) TSPositive.D( __t1)
#define ALIAS_vPositive_DD(__t1) vPositive.DD( __t1)
#define ALIAS_vPositive_D(__t1) vPositive.D( __t1)
#define ALIAS_massPositive_DD(__t1) massPositive.DD( __t1)
#define ALIAS_massPositive_D(__t1) massPositive.D( __t1)


namespace GoddardRocketDefine {

  /*\
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer GoddardRocket::Hxp_numEqns() const { return 4; }

  void
  GoddardRocket::Hxp_eval(
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
    real_type t2   = P__[iP_TimeSize];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_h];
    real_type t5   = X__[iX_v];
    real_type t6   = DD_D_1(t4, t5);
    real_type t7   = X__[iX_m];
    real_type t8   = 1.0 / t7;
    result__[ 0   ] = -t8 * t6 * t3;
    real_type t11  = L__[iL_lambda1__xo];
    real_type t13  = DD_D_2(t4, t5);
    result__[ 1   ] = -t8 * t13 * t3 + t2 * t11;
    real_type t16  = ModelPars[iM_Tmax];
    real_type t18  = U__[iU_w] + 1;
    real_type t21  = DD(t4, t5);
    real_type t22  = t18 * t16 / 2 - t21;
    real_type t23  = t7 * t7;
    result__[ 2   ] = -1.0 / t23 * t22 * t3;
    result__[ 3   ] = t5 * t11 + (t8 * t22 - ModelPars[iM_g]) * t1 - 1.0 / ModelPars[iM_Ve] * t18 * t16 * L__[iL_lambda3__xo] / 2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DHxpDxpu_numRows() const { return 4; }
  integer GoddardRocket::DHxpDxpu_numCols() const { return 5; }
  integer GoddardRocket::DHxpDxpu_nnz()     const { return 17; }

  void
  GoddardRocket::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 3   ;
    iIndex[12] = 2   ; jIndex[12] = 4   ;
    iIndex[13] = 3   ; jIndex[13] = 0   ;
    iIndex[14] = 3   ; jIndex[14] = 1   ;
    iIndex[15] = 3   ; jIndex[15] = 2   ;
    iIndex[16] = 3   ; jIndex[16] = 4   ;
  }


  void
  GoddardRocket::DHxpDxpu_sparse(
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
    real_type t3   = P__[iP_TimeSize] * t1;
    real_type t4   = X__[iX_h];
    real_type t5   = X__[iX_v];
    real_type t6   = DD_D_1_1(t4, t5);
    real_type t7   = X__[iX_m];
    real_type t8   = 1.0 / t7;
    result__[ 0   ] = -t8 * t6 * t3;
    real_type t11  = DD_D_1_2(t4, t5);
    result__[ 1   ] = -t8 * t11 * t3;
    real_type t14  = DD_D_1(t4, t5);
    real_type t15  = t7 * t7;
    real_type t16  = 1.0 / t15;
    result__[ 2   ] = t16 * t14 * t3;
    result__[ 3   ] = -t8 * t14 * t1;
    result__[ 4   ] = result__[1];
    real_type t20  = DD_D_2_2(t4, t5);
    result__[ 5   ] = -t8 * t20 * t3;
    real_type t23  = DD_D_2(t4, t5);
    result__[ 6   ] = t16 * t23 * t3;
    result__[ 7   ] = -t8 * t23 * t1 + L__[iL_lambda1__xo];
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    real_type t28  = ModelPars[iM_Tmax];
    real_type t33  = DD(t4, t5);
    real_type t34  = (U__[iU_w] + 1) * t28 / 2 - t33;
    result__[ 10  ] = 2 / t15 / t7 * t34 * t3;
    result__[ 11  ] = -t16 * t34 * t1;
    result__[ 12  ] = -t16 * t28 * t3 / 2;
    result__[ 13  ] = result__[3];
    result__[ 14  ] = result__[7];
    result__[ 15  ] = result__[11];
    result__[ 16  ] = t8 * t28 * t1 / 2 - 1.0 / ModelPars[iM_Ve] * t28 * L__[iL_lambda3__xo] / 2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 17, i_segment );
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

  integer GoddardRocket::Hu_numEqns() const { return 1; }

  void
  GoddardRocket::Hu_eval(
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
    real_type t5   = 0.314159265358979323846264338328e1 * U__[iU_w] / 2;
    real_type t6   = sin(t5);
    real_type t7   = cos(t5);
    real_type t12  = P__[iP_TimeSize];
    real_type t14  = ModelPars[iM_Tmax];
    result__[ 0   ] = 1.0 / t7 * t6 * ModelPars[iM_epsilon] * 0.314159265358979323846264338328e1 / 2 + 1.0 / X__[iX_m] * t14 * t12 * L__[iL_lambda2__xo] / 2 - 1.0 / ModelPars[iM_Ve] * t14 * t12 * L__[iL_lambda3__xo] / 2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

}

// EOF: GoddardRocket_Methods_AdjointODE.cc
