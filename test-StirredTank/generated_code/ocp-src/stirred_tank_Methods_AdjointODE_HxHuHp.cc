/*-----------------------------------------------------------------------*\
 |  file: stirred_tank_Methods_AdjointODE.cc                             |
 |                                                                       |
 |  version: 1.0   date 20/1/2023                                        |
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


#include "stirred_tank.hh"
#include "stirred_tank_Pars.hh"

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
#define ALIAS_u4Control_D_3(__t1, __t2, __t3) u4Control.D_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2(__t1, __t2, __t3) u4Control.D_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1(__t1, __t2, __t3) u4Control.D_1( __t1, __t2, __t3)
#define ALIAS_u4Control_D_3_3(__t1, __t2, __t3) u4Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2_3(__t1, __t2, __t3) u4Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2_2(__t1, __t2, __t3) u4Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_3(__t1, __t2, __t3) u4Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_2(__t1, __t2, __t3) u4Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_1(__t1, __t2, __t3) u4Control.D_1_1( __t1, __t2, __t3)
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


namespace stirred_tankDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer stirred_tank::Hxp_numEqns() const { return 8; }

  void
  stirred_tank::Hxp_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = U__[iU_u1];
    real_type t3   = U__[iU_u2];
    real_type t4   = U__[iU_u4];
    real_type t5   = X__[iX_x2];
    real_type t7   = X__[iX_x6];
    real_type t8   = U__[iU_u3];
    real_type t13  = L__[iL_lambda2__xo];
    real_type t14  = t5 * t13;
    real_type t16  = L__[iL_lambda4__xo];
    real_type t19  = L__[iL_lambda6__xo];
    real_type t23  = L__[iL_lambda7__xo];
    real_type t27  = L__[iL_lambda8__xo];
    result__[ 0   ] = (-t2 - t3 - t4 - 0.176e2 * t5 - 23 * t8 * t7) * t1 - 0.176e2 * t14 + 0.352e2 * t5 * t16 - 23 * t8 * t7 * t19 + 46 * t8 * t7 * t23 + (0.58e1 * t2 + 0.58e1 * t3 + 0.58e1 * t4) * t27;
    real_type t33  = X__[iX_x1];
    real_type t34  = t33 * t1;
    real_type t37  = X__[iX_x3];
    real_type t41  = L__[iL_lambda3__xo];
    real_type t46  = L__[iL_lambda5__xo];
    result__[ 1   ] = -0.176e2 * t34 + (-t2 - t3 - t4 - 0.176e2 * t33 - 146 * t37) * t13 - 73 * t37 * t41 + 0.352e2 * t33 * t16 + 219 * t37 * t46;
    result__[ 2   ] = -146 * t14 + (-t2 - t3 - t4 - 73 * t5) * t41 + 219 * t5 * t46;
    real_type t55  = X__[iX_x5];
    real_type t63  = t2 + t3 + t4;
    result__[ 3   ] = (-t2 - t3 - t4 - 0.513e2 * t55) * t16 - 0.513e2 * t55 * t46 + 102 * t55 * t19 + 23 * t63 * t27;
    real_type t66  = X__[iX_x4];
    result__[ 4   ] = -0.513e2 * t66 * t16 + (-t2 - t3 - t4 - 0.513e2 * t66) * t46 + 102 * t66 * t19 + 11 * t63 * t27;
    result__[ 5   ] = -23 * t8 * t34 + (-23 * t8 * t33 - t2 - t3 - t4) * t19 + 46 * t8 * t33 * t23 + 28 * t63 * t27;
    result__[ 6   ] = -t63 * t23 + 35 * t63 * t27;
    result__[ 7   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 8, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::DHxpDxlpu_numRows() const { return 8; }
  integer stirred_tank::DHxpDxlpu_numCols() const { return 20; }
  integer stirred_tank::DHxpDxlpu_nnz()     const { return 59; }

  void
  stirred_tank::DHxpDxlpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 8   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 11  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 13  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 14  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 15  ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 16  ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 17  ;
    iIndex[10] = 0   ; jIndex[10] = 18  ;
    iIndex[11] = 0   ; jIndex[11] = 19  ;
    iIndex[12] = 1   ; jIndex[12] = 0   ;
    iIndex[13] = 1   ; jIndex[13] = 2   ;
    iIndex[14] = 1   ; jIndex[14] = 8   ;
    iIndex[15] = 1   ; jIndex[15] = 9   ;
    iIndex[16] = 1   ; jIndex[16] = 10  ;
    iIndex[17] = 1   ; jIndex[17] = 11  ;
    iIndex[18] = 1   ; jIndex[18] = 12  ;
    iIndex[19] = 1   ; jIndex[19] = 16  ;
    iIndex[20] = 1   ; jIndex[20] = 17  ;
    iIndex[21] = 1   ; jIndex[21] = 19  ;
    iIndex[22] = 2   ; jIndex[22] = 1   ;
    iIndex[23] = 2   ; jIndex[23] = 9   ;
    iIndex[24] = 2   ; jIndex[24] = 10  ;
    iIndex[25] = 2   ; jIndex[25] = 12  ;
    iIndex[26] = 2   ; jIndex[26] = 16  ;
    iIndex[27] = 2   ; jIndex[27] = 17  ;
    iIndex[28] = 2   ; jIndex[28] = 19  ;
    iIndex[29] = 3   ; jIndex[29] = 4   ;
    iIndex[30] = 3   ; jIndex[30] = 11  ;
    iIndex[31] = 3   ; jIndex[31] = 12  ;
    iIndex[32] = 3   ; jIndex[32] = 13  ;
    iIndex[33] = 3   ; jIndex[33] = 15  ;
    iIndex[34] = 3   ; jIndex[34] = 16  ;
    iIndex[35] = 3   ; jIndex[35] = 17  ;
    iIndex[36] = 3   ; jIndex[36] = 19  ;
    iIndex[37] = 4   ; jIndex[37] = 3   ;
    iIndex[38] = 4   ; jIndex[38] = 11  ;
    iIndex[39] = 4   ; jIndex[39] = 12  ;
    iIndex[40] = 4   ; jIndex[40] = 13  ;
    iIndex[41] = 4   ; jIndex[41] = 15  ;
    iIndex[42] = 4   ; jIndex[42] = 16  ;
    iIndex[43] = 4   ; jIndex[43] = 17  ;
    iIndex[44] = 4   ; jIndex[44] = 19  ;
    iIndex[45] = 5   ; jIndex[45] = 0   ;
    iIndex[46] = 5   ; jIndex[46] = 8   ;
    iIndex[47] = 5   ; jIndex[47] = 13  ;
    iIndex[48] = 5   ; jIndex[48] = 14  ;
    iIndex[49] = 5   ; jIndex[49] = 15  ;
    iIndex[50] = 5   ; jIndex[50] = 16  ;
    iIndex[51] = 5   ; jIndex[51] = 17  ;
    iIndex[52] = 5   ; jIndex[52] = 18  ;
    iIndex[53] = 5   ; jIndex[53] = 19  ;
    iIndex[54] = 6   ; jIndex[54] = 14  ;
    iIndex[55] = 6   ; jIndex[55] = 15  ;
    iIndex[56] = 6   ; jIndex[56] = 16  ;
    iIndex[57] = 6   ; jIndex[57] = 17  ;
    iIndex[58] = 6   ; jIndex[58] = 19  ;
  }


  void
  stirred_tank::DHxpDxlpu_sparse(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda1__xo];
    real_type t3   = L__[iL_lambda2__xo];
    real_type t5   = L__[iL_lambda4__xo];
    result__[ 0   ] = -0.176e2 * t1 - 0.176e2 * t3 + 0.352e2 * t5;
    real_type t7   = U__[iU_u3];
    real_type t10  = L__[iL_lambda6__xo];
    real_type t13  = L__[iL_lambda7__xo];
    result__[ 1   ] = -23 * t7 * t1 - 23 * t7 * t10 + 46 * t7 * t13;
    real_type t16  = U__[iU_u1];
    real_type t17  = U__[iU_u2];
    real_type t18  = U__[iU_u4];
    real_type t19  = X__[iX_x2];
    real_type t20  = 0.176e2 * t19;
    real_type t21  = X__[iX_x6];
    real_type t22  = t7 * t21;
    real_type t23  = 23 * t22;
    result__[ 2   ] = -t16 - t17 - t18 - t20 - t23;
    result__[ 3   ] = -t20;
    result__[ 4   ] = 0.352e2 * t19;
    result__[ 5   ] = -t23;
    result__[ 6   ] = 46 * t22;
    result__[ 7   ] = 0.58e1 * t16 + 0.58e1 * t17 + 0.58e1 * t18;
    real_type t27  = L__[iL_lambda8__xo];
    result__[ 8   ] = -t1 + 0.58e1 * t27;
    result__[ 9   ] = result__[8];
    result__[ 10  ] = -23 * t21 * t1 - 23 * t21 * t10 + 46 * t21 * t13;
    result__[ 11  ] = result__[9];
    result__[ 12  ] = result__[0];
    real_type t36  = L__[iL_lambda3__xo];
    real_type t38  = L__[iL_lambda5__xo];
    result__[ 13  ] = -146 * t3 - 73 * t36 + 219 * t38;
    real_type t40  = X__[iX_x1];
    result__[ 14  ] = -0.176e2 * t40;
    real_type t42  = X__[iX_x3];
    result__[ 15  ] = -t16 - t17 - t18 + result__[14] - 146 * t42;
    result__[ 16  ] = -73 * t42;
    result__[ 17  ] = 0.352e2 * t40;
    result__[ 18  ] = 219 * t42;
    result__[ 19  ] = -t3;
    result__[ 20  ] = result__[19];
    result__[ 21  ] = result__[20];
    result__[ 22  ] = result__[13];
    result__[ 23  ] = -146 * t19;
    result__[ 24  ] = -t16 - t17 - t18 - 73 * t19;
    result__[ 25  ] = 219 * t19;
    result__[ 26  ] = -t36;
    result__[ 27  ] = result__[26];
    result__[ 28  ] = result__[27];
    result__[ 29  ] = -0.513e2 * t5 - 0.513e2 * t38 + 102 * t10;
    real_type t50  = X__[iX_x5];
    real_type t51  = 0.513e2 * t50;
    result__[ 30  ] = -t16 - t17 - t18 - t51;
    result__[ 31  ] = -t51;
    result__[ 32  ] = 102 * t50;
    real_type t52  = t16 + t17 + t18;
    result__[ 33  ] = 23 * t52;
    result__[ 34  ] = -t5 + 23 * t27;
    result__[ 35  ] = result__[34];
    result__[ 36  ] = result__[35];
    result__[ 37  ] = result__[29];
    real_type t54  = X__[iX_x4];
    result__[ 38  ] = -0.513e2 * t54;
    result__[ 39  ] = -t16 - t17 - t18 + result__[38];
    result__[ 40  ] = 102 * t54;
    result__[ 41  ] = 11 * t52;
    result__[ 42  ] = -t38 + 11 * t27;
    result__[ 43  ] = result__[42];
    result__[ 44  ] = result__[43];
    result__[ 45  ] = result__[1];
    real_type t57  = t7 * t40;
    result__[ 46  ] = -23 * t57;
    result__[ 47  ] = result__[46] - t16 - t17 - t18;
    result__[ 48  ] = 46 * t57;
    result__[ 49  ] = 28 * t52;
    result__[ 50  ] = -t10 + 28 * t27;
    result__[ 51  ] = result__[50];
    result__[ 52  ] = -23 * t40 * t1 - 23 * t40 * t10 + 46 * t40 * t13;
    result__[ 53  ] = result__[51];
    result__[ 54  ] = -t52;
    result__[ 55  ] = 35 * t52;
    result__[ 56  ] = -t13 + 35 * t27;
    result__[ 57  ] = result__[56];
    result__[ 58  ] = result__[57];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxlpu_sparse", 59, i_segment );
  }

}

// EOF: stirred_tank_Methods_AdjointODE.cc
