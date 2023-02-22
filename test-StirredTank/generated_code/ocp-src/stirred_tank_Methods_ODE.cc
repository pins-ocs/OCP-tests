/*-----------------------------------------------------------------------*\
 |  file: stirred_tank_Methods_ODE.cc                                    |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer stirred_tank::ode_numEqns() const { return 8; }

  void
  stirred_tank::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u4];
    real_type t2   = U__[iU_u1];
    real_type t3   = U__[iU_u2];
    real_type t4   = t2 + t3 + t1;
    real_type t5   = X__[iX_x1];
    real_type t6   = t5 * t4;
    real_type t7   = X__[iX_x2];
    real_type t8   = t7 * t5;
    real_type t9   = 0.88e2 / 5.0 * t8;
    real_type t10  = X__[iX_x6];
    real_type t12  = U__[iU_u3];
    real_type t13  = t12 * t10 * t5;
    real_type t14  = 23 * t13;
    result__[ 0   ] = t1 - t6 - t9 - t14 - V__[0];
    real_type t17  = X__[iX_x3];
    real_type t18  = t17 * t7;
    result__[ 1   ] = -t7 * t4 - 146 * t18 + t2 - t9 - V__[1];
    result__[ 2   ] = -t17 * t4 - 73 * t18 + t3 - V__[2];
    real_type t24  = X__[iX_x4];
    real_type t27  = X__[iX_x5];
    real_type t28  = t27 * t24;
    real_type t29  = 0.513e3 / 0.10e2 * t28;
    result__[ 3   ] = -t24 * t4 + 0.176e3 / 5.0 * t8 - t29 - V__[3];
    result__[ 4   ] = -t27 * t4 + 219 * t18 - t29 - V__[4];
    result__[ 5   ] = -t10 * t4 - t14 + 102 * t28 - V__[5];
    real_type t37  = X__[iX_x7];
    result__[ 6   ] = -t37 * t4 + 46 * t13 - V__[6];
    real_type t51  = t12 * t12;
    result__[ 7   ] = 0.29e2 / 5.0 * t6 - 0.29e2 / 5.0 * t1 - 0.37e2 / 0.10e2 * t2 - 0.41e2 / 0.10e2 * t3 + (23 * t24 + 11 * t27 + 28 * t10 + 35 * t37) * t4 - 5 * t51 - 9.0 / 0.100e3 - V__[7];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::DodeDxpuv_numRows() const { return 8; }
  integer stirred_tank::DodeDxpuv_numCols() const { return 20; }
  integer stirred_tank::DodeDxpuv_nnz()     const { return 64; }

  void
  stirred_tank::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 9   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 10  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 11  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 12  ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 1   ;
    iIndex[10] = 1   ; jIndex[10] = 2   ;
    iIndex[11] = 1   ; jIndex[11] = 8   ;
    iIndex[12] = 1   ; jIndex[12] = 9   ;
    iIndex[13] = 1   ; jIndex[13] = 11  ;
    iIndex[14] = 1   ; jIndex[14] = 13  ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 2   ;
    iIndex[17] = 2   ; jIndex[17] = 8   ;
    iIndex[18] = 2   ; jIndex[18] = 9   ;
    iIndex[19] = 2   ; jIndex[19] = 11  ;
    iIndex[20] = 2   ; jIndex[20] = 14  ;
    iIndex[21] = 3   ; jIndex[21] = 0   ;
    iIndex[22] = 3   ; jIndex[22] = 1   ;
    iIndex[23] = 3   ; jIndex[23] = 3   ;
    iIndex[24] = 3   ; jIndex[24] = 4   ;
    iIndex[25] = 3   ; jIndex[25] = 8   ;
    iIndex[26] = 3   ; jIndex[26] = 9   ;
    iIndex[27] = 3   ; jIndex[27] = 11  ;
    iIndex[28] = 3   ; jIndex[28] = 15  ;
    iIndex[29] = 4   ; jIndex[29] = 1   ;
    iIndex[30] = 4   ; jIndex[30] = 2   ;
    iIndex[31] = 4   ; jIndex[31] = 3   ;
    iIndex[32] = 4   ; jIndex[32] = 4   ;
    iIndex[33] = 4   ; jIndex[33] = 8   ;
    iIndex[34] = 4   ; jIndex[34] = 9   ;
    iIndex[35] = 4   ; jIndex[35] = 11  ;
    iIndex[36] = 4   ; jIndex[36] = 16  ;
    iIndex[37] = 5   ; jIndex[37] = 0   ;
    iIndex[38] = 5   ; jIndex[38] = 3   ;
    iIndex[39] = 5   ; jIndex[39] = 4   ;
    iIndex[40] = 5   ; jIndex[40] = 5   ;
    iIndex[41] = 5   ; jIndex[41] = 8   ;
    iIndex[42] = 5   ; jIndex[42] = 9   ;
    iIndex[43] = 5   ; jIndex[43] = 10  ;
    iIndex[44] = 5   ; jIndex[44] = 11  ;
    iIndex[45] = 5   ; jIndex[45] = 17  ;
    iIndex[46] = 6   ; jIndex[46] = 0   ;
    iIndex[47] = 6   ; jIndex[47] = 5   ;
    iIndex[48] = 6   ; jIndex[48] = 6   ;
    iIndex[49] = 6   ; jIndex[49] = 8   ;
    iIndex[50] = 6   ; jIndex[50] = 9   ;
    iIndex[51] = 6   ; jIndex[51] = 10  ;
    iIndex[52] = 6   ; jIndex[52] = 11  ;
    iIndex[53] = 6   ; jIndex[53] = 18  ;
    iIndex[54] = 7   ; jIndex[54] = 0   ;
    iIndex[55] = 7   ; jIndex[55] = 3   ;
    iIndex[56] = 7   ; jIndex[56] = 4   ;
    iIndex[57] = 7   ; jIndex[57] = 5   ;
    iIndex[58] = 7   ; jIndex[58] = 6   ;
    iIndex[59] = 7   ; jIndex[59] = 8   ;
    iIndex[60] = 7   ; jIndex[60] = 9   ;
    iIndex[61] = 7   ; jIndex[61] = 10  ;
    iIndex[62] = 7   ; jIndex[62] = 11  ;
    iIndex[63] = 7   ; jIndex[63] = 19  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  stirred_tank::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u1];
    real_type t2   = U__[iU_u2];
    real_type t3   = U__[iU_u4];
    real_type t4   = X__[iX_x2];
    real_type t5   = 0.88e2 / 5.0 * t4;
    real_type t6   = X__[iX_x6];
    real_type t7   = U__[iU_u3];
    real_type t8   = t7 * t6;
    real_type t9   = 23 * t8;
    result__[ 0   ] = -t1 - t2 - t3 - t5 - t9;
    real_type t10  = X__[iX_x1];
    result__[ 1   ] = -0.88e2 / 5.0 * t10;
    real_type t12  = t7 * t10;
    result__[ 2   ] = -23 * t12;
    result__[ 3   ] = -t10;
    result__[ 4   ] = result__[3];
    real_type t14  = t6 * t10;
    result__[ 5   ] = -23 * t14;
    result__[ 6   ] = 1 + result__[4];
    result__[ 7   ] = -1;
    result__[ 8   ] = -t5;
    real_type t16  = X__[iX_x3];
    result__[ 9   ] = -t1 - t2 - t3 + result__[1] - 146 * t16;
    result__[ 10  ] = -146 * t4;
    result__[ 11  ] = 1 - t4;
    result__[ 12  ] = -t4;
    result__[ 13  ] = result__[12];
    result__[ 14  ] = -1;
    result__[ 15  ] = -73 * t16;
    result__[ 16  ] = -t1 - t2 - t3 - 73 * t4;
    result__[ 17  ] = -t16;
    result__[ 18  ] = 1 + result__[17];
    result__[ 19  ] = result__[17];
    result__[ 20  ] = -1;
    result__[ 21  ] = 0.176e3 / 5.0 * t4;
    result__[ 22  ] = 0.176e3 / 5.0 * t10;
    real_type t21  = X__[iX_x5];
    real_type t22  = 0.513e3 / 0.10e2 * t21;
    result__[ 23  ] = -t1 - t2 - t3 - t22;
    real_type t23  = X__[iX_x4];
    result__[ 24  ] = -0.513e3 / 0.10e2 * t23;
    result__[ 25  ] = -t23;
    result__[ 26  ] = result__[25];
    result__[ 27  ] = result__[26];
    result__[ 28  ] = -1;
    result__[ 29  ] = 219 * t16;
    result__[ 30  ] = 219 * t4;
    result__[ 31  ] = -t22;
    result__[ 32  ] = -t1 - t2 - t3 + result__[24];
    result__[ 33  ] = -t21;
    result__[ 34  ] = result__[33];
    result__[ 35  ] = result__[34];
    result__[ 36  ] = -1;
    result__[ 37  ] = -t9;
    result__[ 38  ] = 102 * t21;
    result__[ 39  ] = 102 * t23;
    result__[ 40  ] = result__[2] - t1 - t2 - t3;
    result__[ 41  ] = -t6;
    result__[ 42  ] = result__[41];
    result__[ 43  ] = result__[5];
    result__[ 44  ] = result__[42];
    result__[ 45  ] = -1;
    result__[ 46  ] = 46 * t8;
    result__[ 47  ] = 46 * t12;
    result__[ 48  ] = -t1 - t2 - t3;
    real_type t25  = X__[iX_x7];
    result__[ 49  ] = -t25;
    result__[ 50  ] = result__[49];
    result__[ 51  ] = 46 * t14;
    result__[ 52  ] = result__[50];
    result__[ 53  ] = -1;
    real_type t26  = -result__[48];
    result__[ 54  ] = 0.29e2 / 5.0 * t26;
    result__[ 55  ] = 23 * t26;
    result__[ 56  ] = 11 * t26;
    result__[ 57  ] = 28 * t26;
    result__[ 58  ] = 35 * t26;
    real_type t27  = 0.29e2 / 5.0 * t10;
    real_type t28  = 23 * t23;
    real_type t29  = 11 * t21;
    real_type t30  = 28 * t6;
    real_type t31  = 35 * t25;
    result__[ 59  ] = t27 - 0.37e2 / 0.10e2 + t28 + t29 + t30 + t31;
    result__[ 60  ] = t27 - 0.41e2 / 0.10e2 + t28 + t29 + t30 + t31;
    result__[ 61  ] = -10 * t7;
    result__[ 62  ] = t27 - 0.29e2 / 5.0 + t28 + t29 + t30 + t31;
    result__[ 63  ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 64, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::A_numRows() const { return 8; }
  integer stirred_tank::A_numCols() const { return 8; }
  integer stirred_tank::A_nnz()     const { return 8; }

  void
  stirred_tank::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 7   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  stirred_tank::A_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 8, i_segment );
  }

}

// EOF: stirred_tank_Methods_ODE.cc
