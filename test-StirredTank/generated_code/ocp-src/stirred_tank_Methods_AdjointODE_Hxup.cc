/*-----------------------------------------------------------------------*\
 |  file: stirred_tank_Methods_AdjointODE.cc                             |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[0];
    real_type t2   = U__[iU_u1];
    real_type t3   = U__[iU_u2];
    real_type t4   = U__[iU_u4];
    real_type t5   = X__[iX_x2];
    real_type t7   = X__[iX_x6];
    real_type t8   = U__[iU_u3];
    real_type t13  = MU__[1];
    real_type t14  = t5 * t13;
    real_type t16  = MU__[3];
    real_type t19  = MU__[5];
    real_type t23  = MU__[6];
    real_type t27  = MU__[7];
    real_type t28  = t2 + t3 + t4;
    result__[ 0   ] = (-t2 - t3 - t4 - 0.88e2 / 5.0 * t5 - 23 * t8 * t7) * t1 - 0.88e2 / 5.0 * t14 + 0.176e3 / 5.0 * t5 * t16 - 23 * t8 * t7 * t19 + 46 * t8 * t7 * t23 + 0.29e2 / 5.0 * t28 * t27;
    real_type t31  = X__[iX_x1];
    real_type t32  = t31 * t1;
    real_type t35  = X__[iX_x3];
    real_type t39  = MU__[2];
    real_type t44  = MU__[4];
    result__[ 1   ] = -0.88e2 / 5.0 * t32 + (-t2 - t3 - t4 - 0.88e2 / 5.0 * t31 - 146 * t35) * t13 - 73 * t35 * t39 + 0.176e3 / 5.0 * t31 * t16 + 219 * t35 * t44;
    result__[ 2   ] = -146 * t14 + (-t2 - t3 - t4 - 73 * t5) * t39 + 219 * t5 * t44;
    real_type t53  = X__[iX_x5];
    result__[ 3   ] = (-t2 - t3 - t4 - 0.513e3 / 0.10e2 * t53) * t16 - 0.513e3 / 0.10e2 * t53 * t44 + 102 * t53 * t19 + 23 * t28 * t27;
    real_type t63  = X__[iX_x4];
    result__[ 4   ] = -0.513e3 / 0.10e2 * t63 * t16 + (-t2 - t3 - t4 - 0.513e3 / 0.10e2 * t63) * t44 + 102 * t63 * t19 + 11 * t28 * t27;
    result__[ 5   ] = -23 * t8 * t32 + (-23 * t8 * t31 - t2 - t3 - t4) * t19 + 46 * t8 * t31 * t23 + 28 * t28 * t27;
    result__[ 6   ] = -t28 * t23 + 35 * t28 * t27;
    result__[ 7   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 8, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::DHxpDxpuv_numRows() const { return 8; }
  integer stirred_tank::DHxpDxpuv_numCols() const { return 20; }
  integer stirred_tank::DHxpDxpuv_nnz()     const { return 31; }

  void
  stirred_tank::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 8   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 10  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 11  ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 9   ;
    iIndex[10] = 1   ; jIndex[10] = 11  ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 8   ;
    iIndex[13] = 2   ; jIndex[13] = 9   ;
    iIndex[14] = 2   ; jIndex[14] = 11  ;
    iIndex[15] = 3   ; jIndex[15] = 4   ;
    iIndex[16] = 3   ; jIndex[16] = 8   ;
    iIndex[17] = 3   ; jIndex[17] = 9   ;
    iIndex[18] = 3   ; jIndex[18] = 11  ;
    iIndex[19] = 4   ; jIndex[19] = 3   ;
    iIndex[20] = 4   ; jIndex[20] = 8   ;
    iIndex[21] = 4   ; jIndex[21] = 9   ;
    iIndex[22] = 4   ; jIndex[22] = 11  ;
    iIndex[23] = 5   ; jIndex[23] = 0   ;
    iIndex[24] = 5   ; jIndex[24] = 8   ;
    iIndex[25] = 5   ; jIndex[25] = 9   ;
    iIndex[26] = 5   ; jIndex[26] = 10  ;
    iIndex[27] = 5   ; jIndex[27] = 11  ;
    iIndex[28] = 6   ; jIndex[28] = 8   ;
    iIndex[29] = 6   ; jIndex[29] = 9   ;
    iIndex[30] = 6   ; jIndex[30] = 11  ;
  }


  void
  stirred_tank::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[0];
    real_type t3   = MU__[1];
    real_type t5   = MU__[3];
    result__[ 0   ] = -0.88e2 / 5.0 * t1 - 0.88e2 / 5.0 * t3 + 0.176e3 / 5.0 * t5;
    real_type t7   = U__[iU_u3];
    real_type t10  = MU__[5];
    real_type t13  = MU__[6];
    result__[ 1   ] = -23 * t7 * t1 - 23 * t7 * t10 + 46 * t7 * t13;
    real_type t16  = MU__[7];
    result__[ 2   ] = -t1 + 0.29e2 / 5.0 * t16;
    result__[ 3   ] = result__[2];
    real_type t18  = X__[iX_x6];
    result__[ 4   ] = -23 * t18 * t1 - 23 * t18 * t10 + 46 * t18 * t13;
    result__[ 5   ] = result__[3];
    result__[ 6   ] = result__[0];
    real_type t26  = MU__[2];
    real_type t28  = MU__[4];
    result__[ 7   ] = -146 * t3 - 73 * t26 + 219 * t28;
    result__[ 8   ] = -t3;
    result__[ 9   ] = result__[8];
    result__[ 10  ] = result__[9];
    result__[ 11  ] = result__[7];
    result__[ 12  ] = -t26;
    result__[ 13  ] = result__[12];
    result__[ 14  ] = result__[13];
    result__[ 15  ] = -0.513e3 / 0.10e2 * t5 - 0.513e3 / 0.10e2 * t28 + 102 * t10;
    result__[ 16  ] = -t5 + 23 * t16;
    result__[ 17  ] = result__[16];
    result__[ 18  ] = result__[17];
    result__[ 19  ] = result__[15];
    result__[ 20  ] = -t28 + 11 * t16;
    result__[ 21  ] = result__[20];
    result__[ 22  ] = result__[21];
    result__[ 23  ] = result__[1];
    result__[ 24  ] = -t10 + 28 * t16;
    result__[ 25  ] = result__[24];
    real_type t36  = X__[iX_x1];
    result__[ 26  ] = -23 * t36 * t1 - 23 * t36 * t10 + 46 * t36 * t13;
    result__[ 27  ] = result__[25];
    result__[ 28  ] = -t13 + 35 * t16;
    result__[ 29  ] = result__[28];
    result__[ 30  ] = result__[29];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 31, i_segment );
  }

}

// EOF: stirred_tank_Methods_AdjointODE.cc
