/*-----------------------------------------------------------------------*\
 |  file: stirred_tank_Methods_controls.cc                               |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  stirred_tank::g_fun_eval(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    real_type QM__[1], XM__[8], LM__[8];
    QM__[0] = (QL__[0]+QR__[0])/2;
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    XM__[7] = (XL__[7]+XR__[7])/2;
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    LM__[7] = (LL__[7]+LR__[7])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = UM__[3];
    real_type t3   = UM__[0];
    real_type t4   = UM__[1];
    real_type t5   = t3 + t4 + t2;
    real_type t6   = XM__[0];
    real_type t7   = t6 * t5;
    real_type t8   = XM__[1];
    real_type t9   = t8 * t6;
    real_type t10  = 0.176e2 * t9;
    real_type t11  = XM__[5];
    real_type t13  = UM__[2];
    real_type t14  = t13 * t11 * t6;
    real_type t15  = 23 * t14;
    real_type t20  = XM__[2];
    real_type t21  = t20 * t8;
    real_type t31  = XM__[3];
    real_type t34  = XM__[4];
    real_type t35  = t34 * t31;
    real_type t36  = 0.513e2 * t35;
    real_type t50  = XM__[6];
    real_type t66  = t13 * t13;
    real_type t70  = u1Control(t3, 0, 20);
    real_type t71  = u2Control(t4, 0, 6);
    real_type t72  = u3Control(t13, 0, 4);
    real_type t73  = u4Control(t2, 0, 20);
    real_type result__ = (t2 - t7 - t10 - t15) * LM__[0] + (-t8 * t5 - t10 - 146 * t21 + t3) * LM__[1] + (-t20 * t5 - 73 * t21 + t4) * LM__[2] + (-t31 * t5 + 0.352e2 * t9 - t36) * LM__[3] + (-t34 * t5 + 219 * t21 - t36) * LM__[4] + (-t11 * t5 - t15 + 102 * t35) * LM__[5] + (-t50 * t5 + 46 * t14) * LM__[6] + (0.58e1 * t7 - 0.58e1 * t2 - 0.37e1 * t3 - 0.41e1 * t4 + (23 * t31 + 11 * t34 + 28 * t11 + 35 * t50) * t5 - 5 * t66 - 0.9e-1) * LM__[7] + t70 + t71 + t72 + t73;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer stirred_tank::g_numEqns() const { return 4; }

  void
  stirred_tank::g_eval(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__,
    real_ptr        result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    real_type QM__[1], XM__[8], LM__[8];
    QM__[0] = (QL__[0]+QR__[0])/2;
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    XM__[7] = (XL__[7]+XR__[7])/2;
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    LM__[7] = (LL__[7]+LR__[7])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t2   = XM__[0];
    real_type t3   = t2 * t1;
    real_type t4   = LM__[1];
    real_type t5   = XM__[1];
    real_type t8   = LM__[2];
    real_type t9   = XM__[2];
    real_type t10  = t9 * t8;
    real_type t12  = XM__[3];
    real_type t13  = t12 * LM__[3];
    real_type t15  = XM__[4];
    real_type t16  = t15 * LM__[4];
    real_type t17  = LM__[5];
    real_type t18  = XM__[5];
    real_type t19  = t18 * t17;
    real_type t20  = LM__[6];
    real_type t21  = XM__[6];
    real_type t22  = t21 * t20;
    real_type t23  = LM__[7];
    real_type t24  = 0.58e1 * t2;
    real_type t25  = 23 * t12;
    real_type t26  = 11 * t15;
    real_type t27  = 28 * t18;
    real_type t28  = 35 * t21;
    real_type t32  = ALIAS_u1Control_D_1(UM__[0], 0, 20);
    result__[ 0   ] = -t3 + (1 - t5) * t4 - t10 - t13 - t16 - t19 - t22 + (t24 - 0.37e1 + t25 + t26 + t27 + t28) * t23 + t32;
    real_type t33  = t5 * t4;
    real_type t39  = ALIAS_u2Control_D_1(UM__[1], 0, 6);
    result__[ 1   ] = -t3 - t33 + (1 - t9) * t8 - t13 - t16 - t19 - t22 + (t24 - 0.41e1 + t25 + t26 + t27 + t28) * t23 + t39;
    real_type t48  = UM__[2];
    real_type t51  = ALIAS_u3Control_D_1(t48, 0, 4);
    result__[ 2   ] = -23 * t18 * t2 * t17 + 46 * t18 * t2 * t20 - 23 * t18 * t3 - 10 * t48 * t23 + t51;
    real_type t57  = ALIAS_u4Control_D_1(UM__[3], 0, 20);
    result__[ 3   ] = (1 - t2) * t1 - t33 - t10 - t13 - t16 - t19 - t22 + (t24 - 0.58e1 + t25 + t26 + t27 + t28) * t23 + t57;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::DgDxlxlp_numRows() const { return 4; }
  integer stirred_tank::DgDxlxlp_numCols() const { return 32; }
  integer stirred_tank::DgDxlxlp_nnz()     const { return 102; }

  void
  stirred_tank::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[15] = 0   ; jIndex[15] = 16  ;
    iIndex[16] = 0   ; jIndex[16] = 17  ;
    iIndex[17] = 0   ; jIndex[17] = 18  ;
    iIndex[18] = 0   ; jIndex[18] = 19  ;
    iIndex[19] = 0   ; jIndex[19] = 20  ;
    iIndex[20] = 0   ; jIndex[20] = 21  ;
    iIndex[21] = 0   ; jIndex[21] = 22  ;
    iIndex[22] = 0   ; jIndex[22] = 24  ;
    iIndex[23] = 0   ; jIndex[23] = 25  ;
    iIndex[24] = 0   ; jIndex[24] = 26  ;
    iIndex[25] = 0   ; jIndex[25] = 27  ;
    iIndex[26] = 0   ; jIndex[26] = 28  ;
    iIndex[27] = 0   ; jIndex[27] = 29  ;
    iIndex[28] = 0   ; jIndex[28] = 30  ;
    iIndex[29] = 0   ; jIndex[29] = 31  ;
    iIndex[30] = 1   ; jIndex[30] = 0   ;
    iIndex[31] = 1   ; jIndex[31] = 1   ;
    iIndex[32] = 1   ; jIndex[32] = 2   ;
    iIndex[33] = 1   ; jIndex[33] = 3   ;
    iIndex[34] = 1   ; jIndex[34] = 4   ;
    iIndex[35] = 1   ; jIndex[35] = 5   ;
    iIndex[36] = 1   ; jIndex[36] = 6   ;
    iIndex[37] = 1   ; jIndex[37] = 8   ;
    iIndex[38] = 1   ; jIndex[38] = 9   ;
    iIndex[39] = 1   ; jIndex[39] = 10  ;
    iIndex[40] = 1   ; jIndex[40] = 11  ;
    iIndex[41] = 1   ; jIndex[41] = 12  ;
    iIndex[42] = 1   ; jIndex[42] = 13  ;
    iIndex[43] = 1   ; jIndex[43] = 14  ;
    iIndex[44] = 1   ; jIndex[44] = 15  ;
    iIndex[45] = 1   ; jIndex[45] = 16  ;
    iIndex[46] = 1   ; jIndex[46] = 17  ;
    iIndex[47] = 1   ; jIndex[47] = 18  ;
    iIndex[48] = 1   ; jIndex[48] = 19  ;
    iIndex[49] = 1   ; jIndex[49] = 20  ;
    iIndex[50] = 1   ; jIndex[50] = 21  ;
    iIndex[51] = 1   ; jIndex[51] = 22  ;
    iIndex[52] = 1   ; jIndex[52] = 24  ;
    iIndex[53] = 1   ; jIndex[53] = 25  ;
    iIndex[54] = 1   ; jIndex[54] = 26  ;
    iIndex[55] = 1   ; jIndex[55] = 27  ;
    iIndex[56] = 1   ; jIndex[56] = 28  ;
    iIndex[57] = 1   ; jIndex[57] = 29  ;
    iIndex[58] = 1   ; jIndex[58] = 30  ;
    iIndex[59] = 1   ; jIndex[59] = 31  ;
    iIndex[60] = 2   ; jIndex[60] = 0   ;
    iIndex[61] = 2   ; jIndex[61] = 5   ;
    iIndex[62] = 2   ; jIndex[62] = 8   ;
    iIndex[63] = 2   ; jIndex[63] = 13  ;
    iIndex[64] = 2   ; jIndex[64] = 14  ;
    iIndex[65] = 2   ; jIndex[65] = 15  ;
    iIndex[66] = 2   ; jIndex[66] = 16  ;
    iIndex[67] = 2   ; jIndex[67] = 21  ;
    iIndex[68] = 2   ; jIndex[68] = 24  ;
    iIndex[69] = 2   ; jIndex[69] = 29  ;
    iIndex[70] = 2   ; jIndex[70] = 30  ;
    iIndex[71] = 2   ; jIndex[71] = 31  ;
    iIndex[72] = 3   ; jIndex[72] = 0   ;
    iIndex[73] = 3   ; jIndex[73] = 1   ;
    iIndex[74] = 3   ; jIndex[74] = 2   ;
    iIndex[75] = 3   ; jIndex[75] = 3   ;
    iIndex[76] = 3   ; jIndex[76] = 4   ;
    iIndex[77] = 3   ; jIndex[77] = 5   ;
    iIndex[78] = 3   ; jIndex[78] = 6   ;
    iIndex[79] = 3   ; jIndex[79] = 8   ;
    iIndex[80] = 3   ; jIndex[80] = 9   ;
    iIndex[81] = 3   ; jIndex[81] = 10  ;
    iIndex[82] = 3   ; jIndex[82] = 11  ;
    iIndex[83] = 3   ; jIndex[83] = 12  ;
    iIndex[84] = 3   ; jIndex[84] = 13  ;
    iIndex[85] = 3   ; jIndex[85] = 14  ;
    iIndex[86] = 3   ; jIndex[86] = 15  ;
    iIndex[87] = 3   ; jIndex[87] = 16  ;
    iIndex[88] = 3   ; jIndex[88] = 17  ;
    iIndex[89] = 3   ; jIndex[89] = 18  ;
    iIndex[90] = 3   ; jIndex[90] = 19  ;
    iIndex[91] = 3   ; jIndex[91] = 20  ;
    iIndex[92] = 3   ; jIndex[92] = 21  ;
    iIndex[93] = 3   ; jIndex[93] = 22  ;
    iIndex[94] = 3   ; jIndex[94] = 24  ;
    iIndex[95] = 3   ; jIndex[95] = 25  ;
    iIndex[96] = 3   ; jIndex[96] = 26  ;
    iIndex[97] = 3   ; jIndex[97] = 27  ;
    iIndex[98] = 3   ; jIndex[98] = 28  ;
    iIndex[99] = 3   ; jIndex[99] = 29  ;
    iIndex[100] = 3   ; jIndex[100] = 30  ;
    iIndex[101] = 3   ; jIndex[101] = 31  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  stirred_tank::DgDxlxlp_sparse(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__,
    real_ptr        result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    real_type QM__[1], XM__[8], LM__[8];
    QM__[0] = (QL__[0]+QR__[0])/2;
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    XM__[7] = (XL__[7]+XR__[7])/2;
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    LM__[7] = (LL__[7]+LR__[7])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t3   = LM__[7];
    result__[ 0   ] = -t1 / 2 + 0.2900000000e1 * t3;
    result__[ 1   ] = -LM__[1] / 2;
    result__[ 2   ] = -LM__[2] / 2;
    result__[ 3   ] = -LM__[3] / 2 + 0.23e2 / 2.0 * t3;
    result__[ 4   ] = -LM__[4] / 2 + 0.11e2 / 2.0 * t3;
    real_type t15  = LM__[5];
    result__[ 5   ] = -t15 / 2 + 14 * t3;
    real_type t18  = LM__[6];
    result__[ 6   ] = -t18 / 2 + 0.35e2 / 2.0 * t3;
    real_type t21  = XM__[0];
    result__[ 7   ] = -t21 / 2;
    real_type t23  = XM__[1];
    result__[ 8   ] = 1.0 / 2.0 - t23 / 2;
    real_type t25  = XM__[2];
    result__[ 9   ] = -t25 / 2;
    real_type t27  = XM__[3];
    result__[ 10  ] = -t27 / 2;
    real_type t29  = XM__[4];
    result__[ 11  ] = -t29 / 2;
    real_type t31  = XM__[5];
    result__[ 12  ] = -t31 / 2;
    real_type t33  = XM__[6];
    result__[ 13  ] = -t33 / 2;
    real_type t35  = 0.2900000000e1 * t21;
    real_type t36  = 0.23e2 / 2.0 * t27;
    real_type t37  = 0.11e2 / 2.0 * t29;
    real_type t38  = 14 * t31;
    real_type t39  = 0.35e2 / 2.0 * t33;
    result__[ 14  ] = t35 - 0.1850000000e1 + t36 + t37 + t38 + t39;
    result__[ 15  ] = result__[0];
    result__[ 16  ] = result__[1];
    result__[ 17  ] = result__[2];
    result__[ 18  ] = result__[3];
    result__[ 19  ] = result__[4];
    result__[ 20  ] = result__[5];
    result__[ 21  ] = result__[6];
    result__[ 22  ] = result__[7];
    result__[ 23  ] = result__[8];
    result__[ 24  ] = result__[9];
    result__[ 25  ] = result__[10];
    result__[ 26  ] = result__[11];
    result__[ 27  ] = result__[12];
    result__[ 28  ] = result__[13];
    result__[ 29  ] = result__[14];
    result__[ 30  ] = result__[15];
    result__[ 31  ] = result__[16];
    result__[ 32  ] = result__[17];
    result__[ 33  ] = result__[18];
    result__[ 34  ] = result__[19];
    result__[ 35  ] = result__[20];
    result__[ 36  ] = result__[21];
    result__[ 37  ] = result__[22];
    result__[ 38  ] = -t23 / 2;
    result__[ 39  ] = 1.0 / 2.0 - t25 / 2;
    result__[ 40  ] = result__[25];
    result__[ 41  ] = result__[26];
    result__[ 42  ] = result__[27];
    result__[ 43  ] = result__[28];
    result__[ 44  ] = t35 - 0.2050000000e1 + t36 + t37 + t38 + t39;
    result__[ 45  ] = result__[30];
    result__[ 46  ] = result__[31];
    result__[ 47  ] = result__[32];
    result__[ 48  ] = result__[33];
    result__[ 49  ] = result__[34];
    result__[ 50  ] = result__[35];
    result__[ 51  ] = result__[36];
    result__[ 52  ] = result__[37];
    result__[ 53  ] = result__[38];
    result__[ 54  ] = result__[39];
    result__[ 55  ] = result__[40];
    result__[ 56  ] = result__[41];
    result__[ 57  ] = result__[42];
    result__[ 58  ] = result__[43];
    result__[ 59  ] = result__[44];
    result__[ 60  ] = -0.23e2 / 2.0 * t31 * t1 - 0.23e2 / 2.0 * t31 * t15 + 23 * t31 * t18;
    result__[ 61  ] = -0.23e2 / 2.0 * t21 * t1 - 0.23e2 / 2.0 * t21 * t15 + 23 * t21 * t18;
    real_type t54  = t31 * t21;
    result__[ 62  ] = -0.23e2 / 2.0 * t54;
    result__[ 63  ] = result__[62];
    result__[ 64  ] = 23 * t54;
    result__[ 65  ] = -5 * UM__[2];
    result__[ 66  ] = result__[60];
    result__[ 67  ] = result__[61];
    result__[ 68  ] = result__[63];
    result__[ 69  ] = result__[68];
    result__[ 70  ] = result__[64];
    result__[ 71  ] = result__[65];
    result__[ 72  ] = result__[45];
    result__[ 73  ] = result__[46];
    result__[ 74  ] = result__[47];
    result__[ 75  ] = result__[48];
    result__[ 76  ] = result__[49];
    result__[ 77  ] = result__[50];
    result__[ 78  ] = result__[51];
    result__[ 79  ] = 1.0 / 2.0 - t21 / 2;
    result__[ 80  ] = result__[53];
    result__[ 81  ] = result__[24];
    result__[ 82  ] = result__[55];
    result__[ 83  ] = result__[56];
    result__[ 84  ] = result__[57];
    result__[ 85  ] = result__[58];
    result__[ 86  ] = t35 - 0.2900000000e1 + t36 + t37 + t38 + t39;
    result__[ 87  ] = result__[72];
    result__[ 88  ] = result__[73];
    result__[ 89  ] = result__[74];
    result__[ 90  ] = result__[75];
    result__[ 91  ] = result__[76];
    result__[ 92  ] = result__[77];
    result__[ 93  ] = result__[78];
    result__[ 94  ] = result__[79];
    result__[ 95  ] = result__[80];
    result__[ 96  ] = result__[81];
    result__[ 97  ] = result__[82];
    result__[ 98  ] = result__[83];
    result__[ 99  ] = result__[84];
    result__[ 100 ] = result__[85];
    result__[ 101 ] = result__[86];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 102, i_segment );
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
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__,
    real_ptr        result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    real_type QM__[1], XM__[8], LM__[8];
    QM__[0] = (QL__[0]+QR__[0])/2;
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    XM__[7] = (XL__[7]+XR__[7])/2;
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    LM__[7] = (LL__[7]+LR__[7])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_u1Control_D_1_1(UM__[0], 0, 20);
    result__[ 1   ] = ALIAS_u2Control_D_1_1(UM__[1], 0, 6);
    real_type t6   = ALIAS_u3Control_D_1_1(UM__[2], 0, 4);
    result__[ 2   ] = -10 * LM__[7] + t6;
    result__[ 3   ] = ALIAS_u4Control_D_1_1(UM__[3], 0, 20);
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
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "stirred_tank::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: stirred_tank_Methods_controls.cc
