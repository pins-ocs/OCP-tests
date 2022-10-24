/*-----------------------------------------------------------------------*\
 |  file: Zermelo_Methods_AdjointODE.cc                                  |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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


#include "Zermelo.hh"
#include "Zermelo_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)


namespace ZermeloDefine {

  /*\
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Zermelo::Hxp_numEqns() const { return 5; }

  void
  Zermelo::Hxp_eval(
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
    real_type t2   = X__[iX_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x];
    real_type t5   = X__[iX_y];
    real_type t6   = velX_D_1(t4, t5);
    real_type t8   = L__[iL_lambda2__xo];
    real_type t9   = t2 * t8;
    real_type t10  = velY_D_1(t4, t5);
    result__[ 0   ] = t10 * t9 + t6 * t3;
    real_type t12  = velX_D_2(t4, t5);
    real_type t14  = velY_D_2(t4, t5);
    result__[ 1   ] = t12 * t3 + t14 * t9;
    result__[ 2   ] = t2 * t1;
    result__[ 3   ] = t2 * t8;
    real_type t17  = velX(t4, t5);
    real_type t21  = velY(t4, t5);
    real_type t25  = ModelPars[iM_S];
    real_type t27  = U__[iU_u];
    real_type t28  = cos(t27);
    real_type t32  = sin(t27);
    result__[ 4   ] = (X__[iX_vx] + t17) * t1 + (X__[iX_vy] + t21) * t8 + t28 * t25 * L__[iL_lambda3__xo] + t32 * t25 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::DHxpDxpu_numRows() const { return 5; }
  integer Zermelo::DHxpDxpu_numCols() const { return 6; }
  integer Zermelo::DHxpDxpu_nnz()     const { return 13; }

  void
  Zermelo::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 1   ;
    iIndex[10] = 4   ; jIndex[10] = 2   ;
    iIndex[11] = 4   ; jIndex[11] = 3   ;
    iIndex[12] = 4   ; jIndex[12] = 5   ;
  }


  void
  Zermelo::DHxpDxpu_sparse(
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
    real_type t2   = X__[iX_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x];
    real_type t5   = X__[iX_y];
    real_type t6   = velX_D_1_1(t4, t5);
    real_type t8   = L__[iL_lambda2__xo];
    real_type t9   = t2 * t8;
    real_type t10  = velY_D_1_1(t4, t5);
    result__[ 0   ] = t10 * t9 + t6 * t3;
    real_type t12  = velX_D_1_2(t4, t5);
    real_type t14  = velY_D_1_2(t4, t5);
    result__[ 1   ] = t12 * t3 + t14 * t9;
    real_type t16  = velX_D_1(t4, t5);
    real_type t18  = velY_D_1(t4, t5);
    result__[ 2   ] = t16 * t1 + t18 * t8;
    result__[ 3   ] = result__[1];
    real_type t20  = velX_D_2_2(t4, t5);
    real_type t22  = velY_D_2_2(t4, t5);
    result__[ 4   ] = t20 * t3 + t22 * t9;
    real_type t24  = velX_D_2(t4, t5);
    real_type t26  = velY_D_2(t4, t5);
    result__[ 5   ] = t24 * t1 + t26 * t8;
    result__[ 6   ] = t1;
    result__[ 7   ] = t8;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[5];
    result__[ 10  ] = result__[6];
    result__[ 11  ] = result__[7];
    real_type t29  = ModelPars[iM_S];
    real_type t31  = U__[iU_u];
    real_type t32  = sin(t31);
    real_type t36  = cos(t31);
    result__[ 12  ] = -t32 * t29 * L__[iL_lambda3__xo] + t36 * t29 * L__[iL_lambda4__xo];
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

  integer Zermelo::Hu_numEqns() const { return 1; }

  void
  Zermelo::Hu_eval(
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
    real_type t2   = X__[iX_T];
    real_type t4   = ModelPars[iM_S];
    real_type t5   = U__[iU_u];
    real_type t6   = sin(t5);
    real_type t11  = cos(t5);
    result__[ 0   ] = t11 * t4 * t2 * L__[iL_lambda4__xo] - t6 * t4 * t2 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

}

// EOF: Zermelo_Methods_AdjointODE.cc
