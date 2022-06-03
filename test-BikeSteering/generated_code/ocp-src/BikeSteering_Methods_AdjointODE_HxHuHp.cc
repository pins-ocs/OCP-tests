/*-----------------------------------------------------------------------*\
 |  file: BikeSteering_Methods_AdjointODE.cc                             |
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


#include "BikeSteering.hh"
#include "BikeSteering_Pars.hh"

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
#define ALIAS_minimumTimeSize_DD(__t1) minimumTimeSize.DD( __t1)
#define ALIAS_minimumTimeSize_D(__t1) minimumTimeSize.D( __t1)
#define ALIAS_FyControl_D_3(__t1, __t2, __t3) FyControl.D_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2(__t1, __t2, __t3) FyControl.D_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1(__t1, __t2, __t3) FyControl.D_1( __t1, __t2, __t3)
#define ALIAS_FyControl_D_3_3(__t1, __t2, __t3) FyControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2_3(__t1, __t2, __t3) FyControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2_2(__t1, __t2, __t3) FyControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_3(__t1, __t2, __t3) FyControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_2(__t1, __t2, __t3) FyControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_1(__t1, __t2, __t3) FyControl.D_1_1( __t1, __t2, __t3)


namespace BikeSteeringDefine {

  /*\
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BikeSteering::Hxp_numEqns() const { return 3; }

  void
  BikeSteering::Hxp_eval(
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
    real_type t2   = X__[iX_TimeSize];
    result__[ 0   ] = t2 * t1;
    real_type t3   = L__[iL_lambda2__xo];
    real_type t7   = ModelPars[iM_m] * ModelPars[iM_g];
    real_type t8   = ModelPars[iM_h];
    result__[ 1   ] = t8 * t7 * t2 * t3;
    result__[ 2   ] = X__[iX_omega] * t1 + (X__[iX_phi] * t8 * t7 - U__[iU_Fy] * t8) * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BikeSteering::DHxpDxpu_numRows() const { return 3; }
  integer BikeSteering::DHxpDxpu_numCols() const { return 4; }
  integer BikeSteering::DHxpDxpu_nnz()     const { return 5; }

  void
  BikeSteering::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 3   ;
  }


  void
  BikeSteering::DHxpDxpu_sparse(
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
    result__[ 0   ] = L__[iL_lambda1__xo];
    real_type t1   = L__[iL_lambda2__xo];
    real_type t5   = ModelPars[iM_h];
    result__[ 1   ] = t5 * ModelPars[iM_g] * ModelPars[iM_m] * t1;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = -t5 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 5, i_segment );
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

  integer BikeSteering::Hu_numEqns() const { return 1; }

  void
  BikeSteering::Hu_eval(
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
    result__[ 0   ] = -L__[iL_lambda2__xo] * X__[iX_TimeSize] * ModelPars[iM_h];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

}

// EOF: BikeSteering_Methods_AdjointODE.cc
