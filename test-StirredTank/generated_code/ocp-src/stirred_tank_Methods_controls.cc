/*-----------------------------------------------------------------------*\
 |  file: stirred_tank_Methods_controls.cc                               |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  stirred_tank::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u1];
    real_type t2   = u1Control(t1, 0, 20);
    real_type t3   = U__[iU_u2];
    real_type t4   = u2Control(t3, 0, 6);
    real_type t5   = U__[iU_u3];
    real_type t6   = u3Control(t5, 0, 4);
    real_type t7   = U__[iU_u4];
    real_type t8   = u4Control(t7, 0, 20);
    real_type t10  = t1 + t3 + t7;
    real_type t11  = X__[iX_x1];
    real_type t12  = t11 * t10;
    real_type t13  = X__[iX_x2];
    real_type t14  = t13 * t11;
    real_type t15  = 0.88e2 / 5.0 * t14;
    real_type t16  = X__[iX_x6];
    real_type t18  = t5 * t16 * t11;
    real_type t19  = 23 * t18;
    real_type t24  = X__[iX_x3];
    real_type t25  = t24 * t13;
    real_type t35  = X__[iX_x4];
    real_type t38  = X__[iX_x5];
    real_type t39  = t38 * t35;
    real_type t40  = 0.513e3 / 0.10e2 * t39;
    real_type t54  = X__[iX_x7];
    real_type t70  = t5 * t5;
    real_type result__ = t2 + t4 + t6 + t8 + (t7 - t12 - t15 - t19) * MU__[0] + (-t13 * t10 + t1 - t15 - 146 * t25) * MU__[1] + (-t24 * t10 - 73 * t25 + t3) * MU__[2] + (-t35 * t10 + 0.176e3 / 5.0 * t14 - t40) * MU__[3] + (-t38 * t10 + 219 * t25 - t40) * MU__[4] + (-t16 * t10 - t19 + 102 * t39) * MU__[5] + (-t54 * t10 + 46 * t18) * MU__[6] + (0.29e2 / 5.0 * t12 - 0.29e2 / 5.0 * t7 - 0.37e2 / 0.10e2 * t1 - 0.41e2 / 0.10e2 * t3 + (23 * t35 + 11 * t38 + 28 * t16 + 35 * t54) * t10 - 5 * t70 - 9.0 / 0.100e3) * MU__[7];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer stirred_tank::g_numEqns() const { return 4; }

  void
  stirred_tank::g_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t2   = ALIAS_u1Control_D_1(U__[iU_u1], 0, 20);
    real_type t3   = MU__[0];
    real_type t4   = X__[iX_x1];
    real_type t5   = t4 * t3;
    real_type t6   = MU__[1];
    real_type t7   = X__[iX_x2];
    real_type t10  = MU__[2];
    real_type t11  = X__[iX_x3];
    real_type t12  = t11 * t10;
    real_type t14  = X__[iX_x4];
    real_type t15  = t14 * MU__[3];
    real_type t17  = X__[iX_x5];
    real_type t18  = t17 * MU__[4];
    real_type t19  = MU__[5];
    real_type t20  = X__[iX_x6];
    real_type t21  = t20 * t19;
    real_type t22  = MU__[6];
    real_type t23  = X__[iX_x7];
    real_type t24  = t23 * t22;
    real_type t25  = MU__[7];
    real_type t26  = 0.29e2 / 5.0 * t4;
    real_type t27  = 23 * t14;
    real_type t28  = 11 * t17;
    real_type t29  = 28 * t20;
    real_type t30  = 35 * t23;
    result__[ 0   ] = t2 - t5 + (1 - t7) * t6 - t12 - t15 - t18 - t21 - t24 + (t26 - 0.37e2 / 0.10e2 + t27 + t28 + t29 + t30) * t25;
    real_type t34  = ALIAS_u2Control_D_1(U__[iU_u2], 0, 6);
    real_type t35  = t7 * t6;
    result__[ 1   ] = t34 - t5 - t35 + (1 - t11) * t10 - t15 - t18 - t21 - t24 + (t26 - 0.41e2 / 0.10e2 + t27 + t28 + t29 + t30) * t25;
    real_type t40  = U__[iU_u3];
    real_type t41  = ALIAS_u3Control_D_1(t40, 0, 4);
    result__[ 2   ] = -23 * t20 * t4 * t19 + 46 * t20 * t4 * t22 - 23 * t20 * t5 - 10 * t40 * t25 + t41;
    real_type t53  = ALIAS_u4Control_D_1(U__[iU_u4], 0, 20);
    result__[ 3   ] = t53 + (1 - t4) * t3 - t35 - t12 - t15 - t18 - t21 - t24 + (t26 - 0.29e2 / 5.0 + t27 + t28 + t29 + t30) * t25;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::DgDxpm_numRows() const { return 4; }
  integer stirred_tank::DgDxpm_numCols() const { return 16; }
  integer stirred_tank::DgDxpm_nnz()     const { return 51; }

  void
  stirred_tank::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 8   ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 9   ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 10  ;
    iIndex[10] = 0   ; jIndex[10] = 11  ;
    iIndex[11] = 0   ; jIndex[11] = 12  ;
    iIndex[12] = 0   ; jIndex[12] = 13  ;
    iIndex[13] = 0   ; jIndex[13] = 14  ;
    iIndex[14] = 0   ; jIndex[14] = 15  ;
    iIndex[15] = 1   ; jIndex[15] = 0   ;
    iIndex[16] = 1   ; jIndex[16] = 1   ;
    iIndex[17] = 1   ; jIndex[17] = 2   ;
    iIndex[18] = 1   ; jIndex[18] = 3   ;
    iIndex[19] = 1   ; jIndex[19] = 4   ;
    iIndex[20] = 1   ; jIndex[20] = 5   ;
    iIndex[21] = 1   ; jIndex[21] = 6   ;
    iIndex[22] = 1   ; jIndex[22] = 8   ;
    iIndex[23] = 1   ; jIndex[23] = 9   ;
    iIndex[24] = 1   ; jIndex[24] = 10  ;
    iIndex[25] = 1   ; jIndex[25] = 11  ;
    iIndex[26] = 1   ; jIndex[26] = 12  ;
    iIndex[27] = 1   ; jIndex[27] = 13  ;
    iIndex[28] = 1   ; jIndex[28] = 14  ;
    iIndex[29] = 1   ; jIndex[29] = 15  ;
    iIndex[30] = 2   ; jIndex[30] = 0   ;
    iIndex[31] = 2   ; jIndex[31] = 5   ;
    iIndex[32] = 2   ; jIndex[32] = 8   ;
    iIndex[33] = 2   ; jIndex[33] = 13  ;
    iIndex[34] = 2   ; jIndex[34] = 14  ;
    iIndex[35] = 2   ; jIndex[35] = 15  ;
    iIndex[36] = 3   ; jIndex[36] = 0   ;
    iIndex[37] = 3   ; jIndex[37] = 1   ;
    iIndex[38] = 3   ; jIndex[38] = 2   ;
    iIndex[39] = 3   ; jIndex[39] = 3   ;
    iIndex[40] = 3   ; jIndex[40] = 4   ;
    iIndex[41] = 3   ; jIndex[41] = 5   ;
    iIndex[42] = 3   ; jIndex[42] = 6   ;
    iIndex[43] = 3   ; jIndex[43] = 8   ;
    iIndex[44] = 3   ; jIndex[44] = 9   ;
    iIndex[45] = 3   ; jIndex[45] = 10  ;
    iIndex[46] = 3   ; jIndex[46] = 11  ;
    iIndex[47] = 3   ; jIndex[47] = 12  ;
    iIndex[48] = 3   ; jIndex[48] = 13  ;
    iIndex[49] = 3   ; jIndex[49] = 14  ;
    iIndex[50] = 3   ; jIndex[50] = 15  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  stirred_tank::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[0];
    real_type t2   = MU__[7];
    result__[ 0   ] = -t1 + 0.29e2 / 5.0 * t2;
    result__[ 1   ] = -MU__[1];
    result__[ 2   ] = -MU__[2];
    result__[ 3   ] = -MU__[3] + 23 * t2;
    result__[ 4   ] = -MU__[4] + 11 * t2;
    real_type t10  = MU__[5];
    result__[ 5   ] = -t10 + 28 * t2;
    real_type t12  = MU__[6];
    result__[ 6   ] = -t12 + 35 * t2;
    real_type t14  = X__[iX_x1];
    result__[ 7   ] = -t14;
    real_type t15  = X__[iX_x2];
    result__[ 8   ] = 1 - t15;
    result__[ 9   ] = -X__[iX_x3];
    real_type t17  = X__[iX_x4];
    result__[ 10  ] = -t17;
    real_type t18  = X__[iX_x5];
    result__[ 11  ] = -t18;
    real_type t19  = X__[iX_x6];
    result__[ 12  ] = -t19;
    real_type t20  = X__[iX_x7];
    result__[ 13  ] = -t20;
    real_type t21  = 0.29e2 / 5.0 * t14;
    real_type t22  = 23 * t17;
    real_type t23  = 11 * t18;
    real_type t24  = 28 * t19;
    real_type t25  = 35 * t20;
    result__[ 14  ] = t21 - 0.37e2 / 0.10e2 + t22 + t23 + t24 + t25;
    result__[ 15  ] = result__[0];
    result__[ 16  ] = result__[1];
    result__[ 17  ] = result__[2];
    result__[ 18  ] = result__[3];
    result__[ 19  ] = result__[4];
    result__[ 20  ] = result__[5];
    result__[ 21  ] = result__[6];
    result__[ 22  ] = result__[7];
    result__[ 23  ] = -t15;
    result__[ 24  ] = 1 + result__[9];
    result__[ 25  ] = result__[10];
    result__[ 26  ] = result__[11];
    result__[ 27  ] = result__[12];
    result__[ 28  ] = result__[13];
    result__[ 29  ] = t21 - 0.41e2 / 0.10e2 + t22 + t23 + t24 + t25;
    result__[ 30  ] = -23 * t19 * t1 - 23 * t19 * t10 + 46 * t19 * t12;
    result__[ 31  ] = -23 * t14 * t1 - 23 * t14 * t10 + 46 * t14 * t12;
    real_type t38  = t19 * t14;
    result__[ 32  ] = -23 * t38;
    result__[ 33  ] = result__[32];
    result__[ 34  ] = 46 * t38;
    result__[ 35  ] = -10 * U__[iU_u3];
    result__[ 36  ] = result__[15];
    result__[ 37  ] = result__[16];
    result__[ 38  ] = result__[17];
    result__[ 39  ] = result__[18];
    result__[ 40  ] = result__[19];
    result__[ 41  ] = result__[20];
    result__[ 42  ] = result__[21];
    result__[ 43  ] = 1 + result__[22];
    result__[ 44  ] = result__[23];
    result__[ 45  ] = result__[9];
    result__[ 46  ] = result__[25];
    result__[ 47  ] = result__[26];
    result__[ 48  ] = result__[27];
    result__[ 49  ] = result__[28];
    result__[ 50  ] = t21 - 0.29e2 / 5.0 + t22 + t23 + t24 + t25;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 51, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::DgDu_numRows() const { return 4; }
  integer stirred_tank::DgDu_numCols() const { return 4; }
  integer stirred_tank::DgDu_nnz()     const { return 4; }

  void
  stirred_tank::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  stirred_tank::DgDu_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_u1Control_D_1_1(U__[iU_u1], 0, 20);
    result__[ 1   ] = ALIAS_u2Control_D_1_1(U__[iU_u2], 0, 6);
    real_type t4   = ALIAS_u3Control_D_1_1(U__[iU_u3], 0, 4);
    result__[ 2   ] = t4 - 10 * MU__[7];
    result__[ 3   ] = ALIAS_u4Control_D_1_1(U__[iU_u4], 0, 20);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 4, i_segment );
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/

  void
  stirred_tank::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "stirred_tank::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: stirred_tank_Methods_controls.cc
