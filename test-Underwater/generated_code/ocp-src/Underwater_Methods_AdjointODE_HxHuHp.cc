/*-----------------------------------------------------------------------*\
 |  file: Underwater_Methods_AdjointODE.cc                               |
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


#include "Underwater.hh"
#include "Underwater_Pars.hh"

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
#define ALIAS_u3Control_D_3(__t1, __t2, __t3) u3Control.D_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2(__t1, __t2, __t3) u3Control.D_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1(__t1, __t2, __t3) u3Control.D_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3_3(__t1, __t2, __t3) u3Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_3(__t1, __t2, __t3) u3Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_2(__t1, __t2, __t3) u3Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_3(__t1, __t2, __t3) u3Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_2(__t1, __t2, __t3) u3Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_1(__t1, __t2, __t3) u3Control.D_1_1( __t1, __t2, __t3)
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


namespace UnderwaterDefine {

  /*\
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::Hxp_numEqns() const { return 7; }

  void
  Underwater::Hxp_eval(
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
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_vz];
    real_type t5   = X__[iX_theta];
    real_type t6   = cos(t5);
    real_type t8   = X__[iX_vx];
    real_type t9   = sin(t5);
    real_type t11  = t4 * t6 - t9 * t8;
    real_type t13  = L__[iL_lambda2__xo];
    real_type t14  = t2 * t13;
    real_type t17  = -t9 * t4 - t6 * t8;
    result__[ 2   ] = t11 * t3 + t17 * t14;
    real_type t21  = L__[iL_lambda5__xo];
    real_type t22  = t2 * t21;
    real_type t23  = X__[iX_Omega];
    real_type t24  = ModelPars[iM_m1];
    real_type t26  = ModelPars[iM_m3];
    real_type t27  = 1.0 / t26;
    real_type t30  = L__[iL_lambda6__xo];
    real_type t31  = t2 * t30;
    real_type t32  = t26 - t24;
    real_type t35  = 1.0 / ModelPars[iM_inertia];
    result__[ 3   ] = t27 * t24 * t23 * t22 + t35 * t32 * t4 * t31 - t9 * t14 + t6 * t3;
    real_type t40  = L__[iL_lambda4__xo];
    real_type t41  = t2 * t40;
    real_type t43  = 1.0 / t24;
    result__[ 4   ] = -t43 * t26 * t23 * t41 + t35 * t32 * t8 * t31 + t6 * t14 + t9 * t3;
    real_type t49  = L__[iL_lambda3__xo];
    result__[ 5   ] = t27 * t24 * t8 * t22 - t43 * t26 * t4 * t41 + t2 * t49;
    result__[ 6   ] = -t17 * t1 + t11 * t13 + t23 * t49 + (-t43 * t26 * t23 * t4 + t43 * U__[iU_u1]) * t40 + (t27 * t24 * t23 * t8 + t27 * U__[iU_u2]) * t21 + (t35 * t32 * t4 * t8 + t35 * U__[iU_u3]) * t30;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 7, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DHxpDxpu_numRows() const { return 7; }
  integer Underwater::DHxpDxpu_numCols() const { return 10; }
  integer Underwater::DHxpDxpu_nnz()     const { return 22; }

  void
  Underwater::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 6   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 3   ;
    iIndex[10] = 4   ; jIndex[10] = 5   ;
    iIndex[11] = 4   ; jIndex[11] = 6   ;
    iIndex[12] = 5   ; jIndex[12] = 3   ;
    iIndex[13] = 5   ; jIndex[13] = 4   ;
    iIndex[14] = 5   ; jIndex[14] = 6   ;
    iIndex[15] = 6   ; jIndex[15] = 2   ;
    iIndex[16] = 6   ; jIndex[16] = 3   ;
    iIndex[17] = 6   ; jIndex[17] = 4   ;
    iIndex[18] = 6   ; jIndex[18] = 5   ;
    iIndex[19] = 6   ; jIndex[19] = 7   ;
    iIndex[20] = 6   ; jIndex[20] = 8   ;
    iIndex[21] = 6   ; jIndex[21] = 9   ;
  }


  void
  Underwater::DHxpDxpu_sparse(
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
    real_type t4   = X__[iX_vz];
    real_type t5   = X__[iX_theta];
    real_type t6   = sin(t5);
    real_type t8   = X__[iX_vx];
    real_type t9   = cos(t5);
    real_type t11  = -t6 * t4 - t9 * t8;
    real_type t13  = L__[iL_lambda2__xo];
    real_type t14  = t2 * t13;
    real_type t17  = -t9 * t4 + t6 * t8;
    result__[ 0   ] = t11 * t3 + t17 * t14;
    result__[ 1   ] = -t9 * t14 - t6 * t3;
    result__[ 2   ] = -t6 * t14 + t9 * t3;
    result__[ 3   ] = -t17 * t1 + t11 * t13;
    result__[ 4   ] = result__[1];
    real_type t26  = L__[iL_lambda6__xo];
    real_type t28  = ModelPars[iM_m3];
    real_type t29  = ModelPars[iM_m1];
    real_type t32  = 1.0 / ModelPars[iM_inertia];
    real_type t33  = t32 * (t28 - t29);
    result__[ 5   ] = t33 * t2 * t26;
    real_type t34  = L__[iL_lambda5__xo];
    real_type t36  = 1.0 / t28;
    real_type t37  = t36 * t29;
    result__[ 6   ] = t37 * t2 * t34;
    real_type t40  = X__[iX_Omega];
    result__[ 7   ] = t33 * t4 * t26 + t37 * t40 * t34 + t9 * t1 - t6 * t13;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[5];
    real_type t45  = L__[iL_lambda4__xo];
    real_type t47  = 1.0 / t29;
    real_type t48  = t47 * t28;
    result__[ 10  ] = -t48 * t2 * t45;
    result__[ 11  ] = t33 * t8 * t26 - t48 * t40 * t45 + t6 * t1 + t9 * t13;
    result__[ 12  ] = result__[6];
    result__[ 13  ] = result__[10];
    result__[ 14  ] = t37 * t8 * t34 - t48 * t4 * t45 + L__[iL_lambda3__xo];
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[7];
    result__[ 17  ] = result__[11];
    result__[ 18  ] = result__[14];
    result__[ 19  ] = t45 * t47;
    result__[ 20  ] = t34 * t36;
    result__[ 21  ] = t26 * t32;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 22, i_segment );
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

  integer Underwater::Hu_numEqns() const { return 3; }

  void
  Underwater::Hu_eval(
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
    result__[ 0   ] = 1.0 / ModelPars[iM_m1] * t2 * L__[iL_lambda4__xo];
    result__[ 1   ] = 1.0 / ModelPars[iM_m3] * t2 * L__[iL_lambda5__xo];
    result__[ 2   ] = 1.0 / ModelPars[iM_inertia] * t2 * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 3, i_segment );
  }

}

// EOF: Underwater_Methods_AdjointODE.cc
